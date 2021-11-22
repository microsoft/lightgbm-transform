import argparse
import json
import logging
import os
import tempfile
from pathlib import Path

import lightgbm as lgb


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--infer-data-path',
        help='The file path for the inference data.',
    )
    parser.add_argument(
        '--model-path',
        help='The file path for the trained LightGBM model.',
    )
    parser.add_argument(
        '--infer-result',
        help='The file path for the inference result.',
    )
    args, _ = parser.parse_known_args()

    infer_data_path = args.infer_data_path
    model_path = args.model_path
    infer_result = args.infer_result

    logger = logging.getLogger()
    logging.basicConfig(level=logging.DEBUG, format='%(message)s')
    logger.info('>>>>>LightGBM Infer Module>>>>>')
    if os.path.isdir(model_path):
        logger.info(
            '[LightGBM Infer] Directory "{}" is provided, use default file name "lgbm.model"'.format(model_path))
        model_path = os.path.join(model_path, 'lgbm.model')

    if os.path.isdir(infer_result):
        logger.info(
            '[LightGBM Infer] Directory "{}" is provided, use default file name "pred.result"'.format(infer_result))
        infer_result = os.path.join(infer_result, 'pred.result')

    bst = lgb.Booster(model_file=model_path)
    pred_prob = bst.predict(infer_data_path)
    # prepare for evaluation, unnecessary if do not need evaluation.
    parser_config_str = ""
    write_to_parser = False
    label_id = -1
    query_id = -1
    with open(model_path) as fin:
        for line in fin:
            if line.startswith("label_index="):
                label_id = int(line.strip().split("=")[1])
            if line.startswith("[group_column"):
                query_id = int(line.split(":")[1].strip().strip("]"))

            if line.startswith("parser:"):
                write_to_parser = True
                continue
            elif line.startswith("end of parser"):
                write_to_parser = False

            if write_to_parser:
                parser_config_str += line

    parser_config_path = Path(tempfile.mkdtemp()) / "parser_config.json"
    with open(parser_config_path, 'w') as fout:
        fout.write(parser_config_str)
    infer_ds = lgb.Dataset(infer_data_path, params={"parser_config_file": parser_config_path,
                                                    "label": label_id, "query": query_id})
    infer_ds.construct()
    true_label = infer_ds.get_label().astype(int)
    query = infer_ds.get_group().astype(int)
    infer_result_dict = {'pred_prob': pred_prob.tolist(), 'true_label': true_label.tolist(), 'query': query.tolist()}
    with open(infer_result, "w") as fout:
        json.dump(infer_result_dict, fout)
    logger.info('<<<<<LightGBM Infer Module<<<<<')

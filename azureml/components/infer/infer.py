import argparse
import logging
import lightgbm as lgb
import numpy as np
import os
import json


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
    if os.path.isdir(infer_data_path):
        logger.info(
            '[LightGBM Infer] Directory "{}" is provided, use default file name "tp.data"'.format(infer_data_path))
        infer_data_path = os.path.join(infer_data_path, 'tp.data')

    if os.path.isdir(model_path):
        logger.info(
            '[LightGBM Infer] Directory "{}" is provided, use default file name "lgbm.model"'.format(model_path))
        model_path = os.path.join(model_path, 'lgbm.model')

    if os.path.isdir(infer_result):
        logger.info(
            '[LightGBM Infer] Directory "{}" is provided, use default file name "pred.result"'.format(infer_result))
        infer_result = os.path.join(infer_result, 'pred.result')

    bst = lgb.Booster(model_file=model_path)
    pred_p = bst.predict(infer_data_path)
    pred_l = np.argmax(pred_p, axis=1)
    np.savetxt(infer_result, pred_p)
    logger.info('<<<<<LightGBM Infer Module<<<<<')

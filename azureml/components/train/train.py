import argparse
import logging
import os

import lightgbm as lgb


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--train-data-path',
        help='The file path for the training data.',
    )
    parser.add_argument(
        '--parser-config-path',
        help='The json path for parser config.',
    )
    parser.add_argument(
        '--label',
        help='Label column name.',
    )
    parser.add_argument(
        '--model-path',
        help='The output file path for the trained LightGBM model.',
    )
    args, _ = parser.parse_known_args()
    train_data_path = args.train_data_path
    parser_config_path = args.parser_config_path
    label = args.label
    model_path = args.model_path

    logger = logging.getLogger()
    logging.basicConfig(level=logging.DEBUG, format='%(message)s')

    logger.info('>>>>>LightGBM Train Module>>>>>')
    train_data = lgb.Dataset(train_data_path,
                             params={
                                 "parser_config_file": parser_config_path,
                                 "label": f'name:{label}'
                             })
    params = {
        'boosting': 'gbdt',
        'learning_rate': 0.22,
        'objective': 'lambdarank',
        'ndcg_eval_at': "1,3,5",
        'metric_freq': 1,
        'label_gain': ','.join([str(i) for i in range(350)]),
        'metric': 'ndcg',
        'num_trees': 800,
        'num_leaves': 300,
        'min_data_in_leaf': 50,
        'max_bin': 16,
        'query': 0,
        'feature_fraction': 0.15,
        # Make sure the stable result given the same input
        'deterministic': 'true',
        'force_col_wise': 'true'
    }
    bst = lgb.train(params, train_data, valid_sets=[train_data])
    logger.info('Finished training.')
    if os.path.isdir(model_path):
        logger.info(
            '[LightGBM Train] Directory "{}" is provided, use default file name "lgbm.model"'.format(model_path))
        model_path = os.path.join(model_path, 'lgbm.model')

    bst.save_model(model_path)
    logger.info('[LightGBM Train] Save model successfully!')
    logger.info('<<<<<LightGBM Train Module<<<<<')

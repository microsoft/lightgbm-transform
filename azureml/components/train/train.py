import argparse
import logging
import lightgbm as lgb
import numpy as np
import os


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--train-data-path',
        help='The file path for the training data.',
    )
    parser.add_argument(
        '--parser-config-path',
        help='The file path for the feature spec.',
    )
    parser.add_argument(
        '--model-path',
        help='The output file path for the trained LightGBM model.',
    )
    args, _ = parser.parse_known_args()
    train_data_path = args.train_data_path
    parser_config_path = args.parser_config_path
    model_path = args.model_path

    logger = logging.getLogger()
    logging.basicConfig(level=logging.DEBUG, format='%(message)s')

    logger.info('>>>>>LightGBM Train Module>>>>>')
    train_data = lgb.Dataset(train_data_path,
                             params={
                                 "parser_config_file": parser_config_path,
                                 "label": 'name:m:Rating'
                             })
    train_data.construct()

    params = {
        'learning_rate': 0.1,
        'lambda_l1': 0.1,
        'lambda_l2': 0.2,
        'max_depth': 4,
        'objective': 'multiclass',
        'num_class': np.max(train_data.get_label().astype(int)) + 1,
        'seed': 2021,
        'deterministic': 'true',
        'force_col_wise': 'true'
    }

    bst = lgb.train(params, train_data)
    logger.info('Finished training.')
    if os.path.isdir(model_path):
        logger.info(
            '[LightGBM Train] Directory "{}" is provided, use default file name "lgbm.model"'.format(model_path))
        model_path = os.path.join(model_path, 'lgbm.model')

    bst.save_model(model_path)
    logger.info('[LightGBM Train] Save model successfully!')
    logger.info('<<<<<LightGBM Train Module<<<<<')

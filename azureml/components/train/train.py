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
        '--lr',
        help='Learning rate.',
    )
    parser.add_argument(
        '--metric-freq',
        help='Metric frequency.',
    )
    parser.add_argument(
        '--label-gain',
        help='Label gain.',
    )
    parser.add_argument(
        '--num-trees',
        help='Number of trees.',
    )
    parser.add_argument(
        '--num-leaves',
        help='Number of leaves.',
    )
    parser.add_argument(
        '--min-data-in-leaf',
        help='Minimum data in a leaf.',
    )
    parser.add_argument(
        '--max-bin',
        help='Maximum bin.',
    )
    parser.add_argument(
        '--query',
        help='Group column index. Must be the index of transformed feature in parser config.',
    )
    parser.add_argument(
        '--feature-fraction',
        help='Feature fraction.',
    )
    parser.add_argument(
        '--model-path',
        help='The output file path for the trained LightGBM model.',
    )
    args, _ = parser.parse_known_args()
    train_data_path = args.train_data_path
    parser_config_path = args.parser_config_path
    label = args.label
    lr = float(args.lr)
    metric_freq = int(args.metric_freq)
    label_gain = args.label_gain
    num_trees = int(args.num_trees)
    num_leaves = int(args.num_leaves)
    min_data_in_leaf = int(args.min_data_in_leaf)
    max_bin = int(args.max_bin)
    query = int(args.query)
    feature_fraction = float(args.feature_fraction)
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
        'learning_rate': lr,
        'objective': 'lambdarank',
        'ndcg_eval_at': "1,3,5",
        'metric_freq': metric_freq,
        'label_gain': label_gain,
        'metric': 'ndcg',
        'num_trees': num_trees,
        'num_leaves': num_leaves,
        'min_data_in_leaf': min_data_in_leaf,
        'max_bin': max_bin,
        'query': query,
        'feature_fraction': feature_fraction,
        # Make sure the stable result given the same input
        'deterministic': 'true',
        'force_col_wise': 'true'
    }
    logger.info(f'params {params}')
    bst = lgb.train(params, train_data, valid_sets=[train_data])
    logger.info('Finished training.')
    if os.path.isdir(model_path):
        logger.info(
            '[LightGBM Train] Directory "{}" is provided, use default file name "lgbm.model"'.format(model_path))
        model_path = os.path.join(model_path, 'lgbm.model')

    bst.save_model(model_path)
    logger.info('[LightGBM Train] Save model successfully!')
    logger.info('<<<<<LightGBM Train Module<<<<<')

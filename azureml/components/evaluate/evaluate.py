import argparse
import json
import logging
import os
from itertools import islice

import numpy as np
from sklearn.metrics import ndcg_score


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--predict-result',
        help='The predict result for the evaluating data.',
    )
    parser.add_argument(
        '--evaluation-result',
        help='The output evaluation result.',
    )
    args, _ = parser.parse_known_args()
    predict_result = args.predict_result
    evaluation_result = args.evaluation_result
    logger = logging.getLogger()
    logging.basicConfig(level=logging.DEBUG, format='%(message)s')

    logger.info('>>>>>Evaluation Module>>>>>')
    if os.path.isdir(predict_result):
        logger.info('[Evaluation] Directory "{}" is provided, use default file name "pred.result"'.format(predict_result))
        predict_result = os.path.join(predict_result, 'pred.result')

    if os.path.isdir(evaluation_result):
        logger.info('[Evaluation] Directory "{}" is provided, use default file name "evaluation_result"'.format(evaluation_result))
        evaluation_result = os.path.join(evaluation_result, 'evaluation_result')

    with open(predict_result) as fin:
        predict_result_dict = json.load(fin)

    output_list = []
    pred_prob = np.array(predict_result_dict['pred_prob'])
    query = np.array(predict_result_dict["query"]).astype(int)
    true_label = np.array(predict_result_dict["true_label"]).astype(int)
    pred_prob_iter = iter(pred_prob)
    pred_prob_res = [list(islice(pred_prob_iter, 0, q)) for q in query]
    true_label_iter = iter(true_label)
    true_label_res = [list(islice(true_label_iter, 0, q)) for q in query]
    ndcg_scores = []
    for true_relevance, scores in zip(true_label_res, pred_prob_res):
        true_relevance = np.asarray([list(true_relevance)])
        scores = np.asarray([list(scores)])
        ndcg_scores.append(ndcg_score(true_relevance, scores))

    ndcg_scores = np.array(ndcg_scores)
    output_list.append(f'[Evaluation] NDCG on evaluation data: {np.array2string(ndcg_scores)}')
    output_list.append(f'[Evaluation] Average NDCG on evaluation data: {np.average(ndcg_scores)}')
    output_str = '\n'.join(output_list)
    logger.info(output_str)
    with open(evaluation_result, 'w') as fout:
        fout.write(output_str)

    logger.info('<<<<<Evaluation Module<<<<<')

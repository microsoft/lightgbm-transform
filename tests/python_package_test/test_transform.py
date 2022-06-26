import json
from collections import namedtuple
from pathlib import Path

import lightgbm as lgb
import numpy as np
import pandas as pd
import pytest

Dataset = namedtuple('Dataset', ['data', 'parser_config'])


def root_path():
    return Path(__file__).parent.parent / "data"


def init_dataset(data_dir):
    return Dataset(data_dir / "input.tsv", data_dir / "freeform_config.json")


rank_ds = init_dataset(root_path() / "transform_rank_data")
simple_ds = init_dataset(root_path() / "transform_simple_data")


def generate_ds_with_header(ds, out_dir):
    data_path, config_path = out_dir / "input.tsv", out_dir / "freeform_config.json"
    with open(ds.parser_config) as fin:
        config = json.load(fin)

    header_str = config.pop("header")
    with open(config_path, 'w') as fout:
        json.dump(config, fout)

    df = pd.read_csv(ds.data, sep='\t', header=None)
    df.to_csv(data_path, index=False, header=header_str.strip().split('\t'), sep='\t')
    return init_dataset(out_dir)


@pytest.fixture
def simple_ds_with_header(tmp_path):
    return generate_ds_with_header(simple_ds, tmp_path)


@pytest.fixture
def simple_data_no_label(simple_ds_with_header, tmp_path):
    out_path = tmp_path / "simple_input_no_label.tsv"
    df = pd.read_csv(simple_ds_with_header.data, sep='\t', header=0)
    df.drop("labels", axis=1).to_csv(out_path, index=False, sep='\t')
    return out_path


@pytest.fixture
def trained_model_path(tmp_path):
    return tmp_path / "model.txt"


@pytest.fixture
def params():
    return {
        'boosting': 'gbdt',
        'learning_rate': 0.1,
        'label': 3,
        'query': 0,
        'objective': 'lambdarank',
        'metric': 'ndcg',
        'num_trees': 10,
        'num_leaves': 31,
        'label_gain': ','.join([str(i) for i in range(101)]),
        'force_col_wise': True,
        'deterministic': True
    }


@pytest.fixture
def binary_params():
    return {
        'boosting': 'gbdt',
        'learning_rate': 0.1,
        'label': 10,
        'objective': 'binary',
        'metric': 'auc',
        'num_trees': 10,
        'num_leaves': 31,
        'deterministic': True
    }


def test_e2e(params, trained_model_path):
    train_data = lgb.Dataset(rank_ds.data, params={"parser_config_file": rank_ds.parser_config})
    # train and predict.
    bst = lgb.train(params, train_data, valid_sets=[train_data])
    pred = bst.predict(rank_ds.data)
    np.testing.assert_allclose(pred[:5], np.array([0.83267298, 0.388454, 0.35369267, 0.60330376, -1.24218415]))
    # save model.
    bst.save_model(trained_model_path)
    # load model and predict again.
    bst = lgb.Booster(model_file=trained_model_path)
    pred = bst.predict(rank_ds.data)
    np.testing.assert_allclose(pred[:5], np.array([0.83267298, 0.388454, 0.35369267, 0.60330376, -1.24218415]))


def test_train_data_no_header(binary_params, simple_ds_with_header, trained_model_path):
    train_data = lgb.Dataset(simple_ds.data, params={"parser_config_file": simple_ds.parser_config})
    valid_data = lgb.Dataset(simple_ds_with_header.data, params={
        "parser_config_file": simple_ds_with_header.parser_config, "header": True})
    bst = lgb.train(binary_params, train_data, valid_sets=[valid_data])
    expected_pred = 0.4894574
    # predict data with no header.
    pred = bst.predict(simple_ds.data)
    np.testing.assert_allclose(pred[:1], expected_pred)
    # predict data with header.
    pred = bst.predict(simple_ds_with_header.data, data_has_header=True)
    np.testing.assert_allclose(pred[:1], expected_pred)


def test_train_data_with_header(binary_params, simple_ds_with_header):
    train_data = lgb.Dataset(simple_ds_with_header.data, params={
        "parser_config_file": simple_ds_with_header.parser_config, "header": True})
    bst = lgb.train(binary_params, train_data, valid_sets=[train_data])
    expected_pred = 0.4894574
    # predict data with no header.
    pred = bst.predict(simple_ds.data)
    np.testing.assert_allclose(pred[:1], expected_pred)
    # predict data with header.
    pred = bst.predict(simple_ds_with_header.data, data_has_header=True)
    np.testing.assert_allclose(pred[:1], expected_pred)


def test_set_label_by_name(params, capsys):
    train_data = lgb.Dataset(rank_ds.data, params={"parser_config_file": rank_ds.parser_config})
    params['label'] = "name:Rating"
    bst = lgb.train(params, train_data, valid_sets=[train_data])
    captured = capsys.readouterr()
    assert "Using column Rating as label" in captured.out
    pred = bst.predict(rank_ds.data)
    np.testing.assert_allclose(pred[:5], np.array([0.83267298, 0.388454, 0.35369267, 0.60330376, -1.24218415]))


def test_predict_data_no_label(simple_data_no_label, binary_params):
    train_data = lgb.Dataset(simple_ds.data,
                             params={"parser_config_file": simple_ds.parser_config})
    bst = lgb.train(binary_params, train_data, valid_sets=[train_data])
    pred = bst.predict(simple_data_no_label, data_has_header=True)
    np.testing.assert_allclose(pred[:5], np.array([0.4894574, 0.43920928, 0.71112129, 0.43920928, 0.39602784]))


def test_train_label_id_less_than_transformed_feature_num(binary_params):
    train_data = lgb.Dataset(simple_ds.data,
                             params={"parser_config_file": simple_ds.parser_config})
    bst = lgb.train(binary_params, train_data, valid_sets=[train_data])
    pred = bst.predict(simple_ds.data)
    np.testing.assert_allclose(pred[:5], np.array([0.4894574, 0.43920928, 0.71112129, 0.43920928, 0.39602784]))


def test_continue_training(params):
    train_data = lgb.Dataset(rank_ds.data, params={"parser_config_file": rank_ds.parser_config}, free_raw_data = False)
    bst = lgb.train(params, train_data, valid_sets=[train_data])
    # 'num_trees' parameter is 10, which means the number of boosting iteration round is 10 in this case, so the current_iteration is 10.
    assert bst.current_iteration() == 10
    params['num_trees'] = 20
    params['num_leaves'] = 63
    # continue train 20 iterations, finally we could se the current iteration is 30.
    continue_train_bst = lgb.train(params, train_data, valid_sets=[train_data], init_model=bst)
    assert continue_train_bst.current_iteration() == 30

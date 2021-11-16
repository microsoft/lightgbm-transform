LightGBM Transform Tutorial
===========================

The purpose of this document is to give you a tutorial on how to do transformation in LightGBM with `FreeForm2Parser <./examples/freeform2_parser.cpp>`__.

Transformation is a process to convert data/feature from one format to another.
Now we support two kinds of transformations in LightGBM:

-   Linear. Linear transformation, could be adjusted by `slope` and `intercept`.

-   `FreeForm2 <./FreeForm2-Language.rst>`__. FreeForm2 is a more flexible transform, created by Microsoft Core Ranking and used widely over Microsoft production model training.
    As the name indicates, FreeForm2 empowers users to compose a free combination of features as they like. It is expressed by formulas to be applied in the model inputs.
    The surface syntax is s-expression, with parentheses in a LISP-like fashion to delimit. 
    FreeForm2 has implicit type systems and evaluate a single, nested expression that returns a floating-point number.


How to use `FreeForm2Parser`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Installation
------------

See `Installation Guide <./Installation-Guide.rst>`__, install dependencies and `FreeForm2Parser`.

Data preparation
----------------
1.  Input data. Data file used for training or prediction.

    **Note**: only TSV is supported now.

    **Note**: header is a must-have, you could provide header in input data or `parser_config_file`.

2.  Parser config file. The `json` file should contain `className`, `transform` and `header` key-value pairs, below is an example.

    .. code::

        {
            "className":"FreeForm2Parser",
            "transform":"[Input:0]\nLine1=(+ feature_1 feature_2)\nTransform=FreeForm2\nSlope=1\nIntercept=0\n\n[Input:1]\nTransform=FreeForm2\nLine1=(* feature_1 feature_3)\n",
            "header":"feature_0\tfeature_1\tfeature_2\tfeature_3\tfeature_4\tfeature_5\tfeature_6\tfeature_7\tfeature_8\tfeature_9\tlabels"
        }

    **Note**: transform value is the content of transform file.
    Transform file is not a supplement of raw features, but all used for training. Use "Linear" type if you want to keep the original ones.
    See `FreeForm2 language spec <./FreeForm2-Language>`__ and learn more about the grammar.

    **Note**: transformed feature index ranges from 0 to the maximum "Input" value given in transform file.
    By default, will pad 0 as feature value for missing indices within the range.

    **Kindly reminder**: you could auto-generate parser config file with command

    .. code::

        python ./scripts/generate_parser_config.py --class_name your_parser_name --transform_file path/to/transform --header_file path/to/header --parser_config_file path/to/parser_config

**Note**: if no parser config file is given, 
the input data will be used as features directly for training.

Run task
--------

Actually, the use way is the same as previous, no interface change.

.. code::

    train_data = lgb.Dataset("path/to/train.tsv", params={"parser_config_file": "path/to/parser_config.json"})
    valid_data = lgb.Dataset("path/to/valid.tsv", params={"parser_config_file": "path/to/parser_config.json"})
    # train and predict.
    bst = lgb.train(params, train_data, valid_sets=[valid_data])
    pred = bst.predict("path/to/test.tsv")
    # save model.
    bst.save_model(trained_model_path)
    # load model and predict again.
    bst = lgb.Booster(model_file=trained_model_path)
    pred = bst.predict("path/to/test.tsv")

**Note**: parser config will be saved at the bottom of model file, between section flag "parser" and "end of parser".

#!/bin/bash

lgb_python_pkg_dir="./external_libs/LightGBM/python-package"
# compile transformation, lightgbm, and customized parser libs.
mkdir build
# precompile mpi option.
cd build && cmake ../ -DUSE_MPI=ON && make -j4 && cd ../ || exit -1
# copy all shared libs to lightgbm python package directory.
cp ./lib_custom_parser.so ${lgb_python_pkg_dir}/lightgbm && \
cp ./src/lib_transform.so ${lgb_python_pkg_dir}/lightgbm && \
cp ./external_libs/LightGBM/lib_lightgbm.so ${lgb_python_pkg_dir}/lightgbm || exit -1
# modify `basic.py` to load all libs first, or cannot find them when calling python interfaces.
cp ${lgb_python_pkg_dir}/lightgbm/basic.py raw && cat ./scripts/load_precompiled_libs.py ${lgb_python_pkg_dir}/lightgbm/basic.py > tmp && cp tmp ${lgb_python_pkg_dir}/lightgbm/basic.py || exit -1
# install python package
# install scikit-learn to avoid error "ImportError: cannot import name '_LGBMBaseCrossValidator' from 'lightgbm.compat'"
pip install pytest numpy scipy pandas scikit-learn
pip list

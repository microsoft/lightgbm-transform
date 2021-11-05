# run command `sh ./scripts/publish_python_package.sh` in repo root dir.
lgb_python_pkg_dir="./external_libs/LightGBM/python-package"
# compile transformation, lightgbm, and customized parser libs.
# rm -rf build && mkdir build && 
cd build && cmake ../ && make -j4 && cd ../ || exit -1
# copy all shared libs to lightgbm python package directory.
cp ./lib_custom_parser.so ${lgb_python_pkg_dir}/lightgbm && \
cp ./src/lib_transform.so ${lgb_python_pkg_dir}/lightgbm && \
cp ./external_libs/LightGBM/lib_lightgbm.so ${lgb_python_pkg_dir}/lightgbm || exit -1
# modify `basic.py` to load all libs first, or cannot find them when calling python interfaces.
cp ${lgb_python_pkg_dir}/lightgbm/basic.py raw && cat ./scripts/load_precompiled_libs.py ${lgb_python_pkg_dir}/lightgbm/basic.py > tmp && cp tmp ${lgb_python_pkg_dir}/lightgbm/basic.py || exit -1
# pack wheel package.
cd ${lgb_python_pkg_dir} && rm -rf dist/ && python setup.py bdist_wheel --precompile && cd ../../../ || exit -1
# revert changes
mv raw ${lgb_python_pkg_dir}/lightgbm/basic.py && rm -rf raw tmp ${lgb_python_pkg_dir}/lightgbm/*.so || exit -1
# upload package to your pypi, use testpypi as an example.
twine upload --repository testpypi ${lgb_python_pkg_dir}/dist/* || exit -1

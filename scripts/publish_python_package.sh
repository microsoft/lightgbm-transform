# run command `sh ./scripts/publish_python_package.sh` in repo root dir.
lgb_python_pkg_dir="./external_libs/LightGBM/python-package"
# compile transformation, lightgbm, and customized parser libs.
mkdir build
# precompile mpi option.
cd build && cmake ../ -DUSE_MPI=ON && make -j4 && cd ../ || exit -1
# copy all shared libs to lightgbm python package directory.
# modify `basic.py` to load all libs first, or cannot find them when calling python interfaces.
mkdir compile
cp -r ${lgb_python_pkg_dir}/lightgbm ./compile/ || exit -1
mkdir compile/lightgbm/bin
cp ./lib_custom_parser.so ${lgb_python_pkg_dir}/lightgbm/bin && \
cp ./src/lib_transform.so ${lgb_python_pkg_dir}/lightgbm/bin && \
cp ./external_libs/LightGBM/lib_lightgbm.so ${lgb_python_pkg_dir}/lightgbm/bin || exit -1 
cat ./scripts/load_precompiled_libs.py ./compile/lightgbm/basic.py > tmp && cp tmp ./compile/lightgbm/basic.py || exit -1
rm -rf tmp
cp ./scripts/setup.py ./compile/ && cp ./scripts/README.rst ./compile && cp VERSION.txt ./compile && cp ./scripts/MANIFEST.in ./compile || exit -1
# pack wheel package.
cd compile && python setup.py bdist_wheel --precompile && cd ../ || exit -1
# upload package to your pypi, use testpypi as an example.
twine upload --repository pypi compile/dist/* || exit -1
# revert changes.
rm -rf ${lgb_python_pkg_dir}/lightgbm/*.so build compile || exit -1

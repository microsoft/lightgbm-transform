LightGBM Transformation Installation Guide
==========================================

Currently, the transform supported LightGBM can be built with gcc/g++ on linux platform.

The following dependencies should be installed before compilation:

-  `CMake`_ 3.15 or later.

-  gcc/g++ 8 or later.

-  libboost 1.58 or later.

-  `llvm`_ 3.5.1 (exact match) with cmake parameter ``-DLLVM_REQUIRES_RTTI=1``.

-  `bond`_ with cmake parameter ``-DBOND_ENABLE_GRPC=FALSE``.

See below docker file as an example for required dependencies installation.

   .. code::

      FROM ubuntu:20.04
      # Install CMake, gcc, g++, boost.
      RUN apt-get update && apt-get -y upgrade && DEBIAN_FRONTEND="noninteractive" apt-get install -y libboost-all-dev gcc g++ wget cmake git curl
      # Install LLVM with RTTI feature.
      WORKDIR /root
      RUN wget https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-3.5.1.tar.gz && tar zxvf llvmorg-3.5.1.tar.gz
      WORKDIR /root/llvm-project-llvmorg-3.5.1/llvm
      RUN mkdir build && cd build && cmake -DLLVM_REQUIRES_RTTI=1 .. && make -j4 && make install
      # Install bond.
      WORKDIR /root
      RUN git clone --recursive https://github.com/microsoft/bond.git
      RUN DEBIAN_FRONTEND="noninteractive" apt-get install -y clang zlib1g-dev
      RUN curl -sSL https://get.haskellstack.org/ | sh
      WORKDIR /root/bond
      RUN mkdir build && cd build && cmake -DBOND_ENABLE_GRPC=FALSE .. && make -j4 && make install
      ...

To install LightGBM transform version, you could simply run following command:

   .. code::

      pip install lightgbm-transform==3.3.1 --extra-index-url https://test.pypi.org/simple

Alternatively, you could publish your own package with following commands:

   .. code::

      git clone --recursive https://github.com/microsoft/lightgbm-transform/
      cd lightgbm-transform
      # change version and package name in ./external_libs/LightGBM/python-package manually
      # install twine first
      sh ./scripts/publish_python_package.sh


.. _CMake: https://cmake.org/

.. _llvm: https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-3.5.1.tar.gz

.. _bond: https://github.com/microsoft/bond.git

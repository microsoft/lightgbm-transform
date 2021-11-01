Currently, the transform supported LightGBM can be built with gcc/g++ on linux platform.

Linux
^^^^^

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

To build LightGBM transform version, run the following commands:

   .. code::

     git clone -b feat/enable_transform_to_lgbm --recursive git@github.com:microsoft/LightGBM.git
     cd LightGBM
     mkdir build
     cd build
     cmake -DUSE_TRANSFORM=ON ..
     make -j4

**Note**: You can also install from python sdk with command ``python3 setup.py install --transform``.

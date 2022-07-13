#!/bin/bash

# Install CMake, gcc, g++, boost.
sudo apt-get update
sudo apt-get -y upgrade
sudo DEBIAN_FRONTEND="noninteractive" apt-get install -y libboost-all-dev gcc g++ wget cmake git curl libtinfo5
# Install LLVM with RTTI feature.
wget https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-3.5.1.tar.gz && tar zxvf llvmorg-3.5.1.tar.gz
cd ./llvm-project-llvmorg-3.5.1/llvm
mkdir build && cd build && cmake -DLLVM_REQUIRES_RTTI=1 .. && make -j4 && make install
# Install bond.
cd ../../../../
pwd
git clone --recursive https://github.com/microsoft/bond.git
sudo DEBIAN_FRONTEND="noninteractive" apt-get install -y clang zlib1g-dev
curl -sSL https://get.haskellstack.org/ | sh
cd ./bond
mkdir build && cd build && cmake -DBOND_ENABLE_GRPC=FALSE .. && make -j4 && make install
cd ../../
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
sh Miniconda3-latest-Linux-x86_64.sh
conda

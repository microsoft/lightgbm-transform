"""Setup lightgbm-transform package."""
import logging
import struct
import subprocess
import sys
from os import chdir
from pathlib import Path
from platform import system
from shutil import copyfile, copytree, rmtree
from typing import List, Optional, Union

from setuptools import find_packages, setup
from setuptools.command.install import install
from wheel.bdist_wheel import bdist_wheel

sys.path.insert(0, '../external_libs/LightGBM/python-package')

LIGHTGBM_OPTIONS = [
    ('mingw', 'm', 'Compile with MinGW'),
    ('integrated-opencl', None, 'Compile integrated OpenCL version'),
    ('gpu', 'g', 'Compile GPU version'),
    ('cuda', None, 'Compile CUDA version'),
    ('mpi', None, 'Compile MPI version'),
    ('nomp', None, 'Compile version without OpenMP support'),
    ('hdfs', 'h', 'Compile HDFS version'),
    ('bit32', None, 'Compile 32-bit version'),
    ('precompile', 'p', 'Use precompiled library'),
    ('time-costs', None, 'Output time costs for different internal routines'),
    ('boost-root=', None, 'Boost preferred installation prefix'),
    ('boost-dir=', None, 'Directory with Boost package configuration file'),
    ('boost-include-dir=', None, 'Directory containing Boost headers'),
    ('boost-librarydir=', None, 'Preferred Boost library directory'),
    ('opencl-include-dir=', None, 'OpenCL include directory'),
    ('opencl-library=', None, 'Path to OpenCL library')
]


class CustomInstall(install):

    user_options = install.user_options + LIGHTGBM_OPTIONS

    def initialize_options(self) -> None:
        install.initialize_options(self)
        self.mingw = False
        self.integrated_opencl = False
        self.gpu = False
        self.cuda = False
        self.boost_root = None
        self.boost_dir = None
        self.boost_include_dir = None
        self.boost_librarydir = None
        self.opencl_include_dir = None
        self.opencl_library = None
        self.mpi = False
        self.hdfs = False
        self.precompile = True
        self.nomp = False
        self.bit32 = False

    def run(self) -> None:
        if (8 * struct.calcsize("P")) != 64:
            if self.bit32:
                logger.warning("You're installing 32-bit version. "
                               "This version is slow and untested, so use it on your own risk.")
            else:
                raise Exception("Cannot install LightGBM in 32-bit Python, "
                                "please use 64-bit Python instead.")
        LOG_PATH.touch()
        if not self.precompile:
            raise Exception("Only precompilation is supported now.")

        install.run(self)
        if LOG_PATH.is_file():
            LOG_PATH.unlink()


class CustomBdistWheel(bdist_wheel):

    user_options = bdist_wheel.user_options + LIGHTGBM_OPTIONS

    def initialize_options(self) -> None:
        bdist_wheel.initialize_options(self)
        self.mingw = False
        self.integrated_opencl = False
        self.gpu = False
        self.cuda = False
        self.boost_root = None
        self.boost_dir = None
        self.boost_include_dir = None
        self.boost_librarydir = None
        self.opencl_include_dir = None
        self.opencl_library = None
        self.mpi = False
        self.hdfs = False
        self.precompile = False
        self.time_costs = False
        self.nomp = False
        self.bit32 = False

    def finalize_options(self) -> None:
        bdist_wheel.finalize_options(self)

        install = self.reinitialize_command('install')

        install.mingw = self.mingw
        install.integrated_opencl = self.integrated_opencl
        install.gpu = self.gpu
        install.cuda = self.cuda
        install.boost_root = self.boost_root
        install.boost_dir = self.boost_dir
        install.boost_include_dir = self.boost_include_dir
        install.boost_librarydir = self.boost_librarydir
        install.opencl_include_dir = self.opencl_include_dir
        install.opencl_library = self.opencl_library
        install.mpi = self.mpi
        install.hdfs = self.hdfs
        install.precompile = self.precompile
        install.time_costs = self.time_costs
        install.nomp = self.nomp
        install.bit32 = self.bit32


if __name__ == '__main__':
    CURRENT_DIR = Path(__file__).absolute().parent
    LOG_PATH = Path.home() / 'LightGBM_compilation.log'
    LOG_NOTICE = f"The full version of error log was saved into {LOG_PATH}"
    IS_SOURCE_FLAG_PATH = CURRENT_DIR / '_IS_SOURCE_PACKAGE.txt'
    version_path = Path(__file__).parent / "VERSION.txt"
    version = version_path.read_text(encoding='utf-8').strip()
    readme = (CURRENT_DIR / 'README.rst').read_text(encoding='utf-8')

    logging.basicConfig(level=logging.INFO)
    logger = logging.getLogger('LightGBM')

    setup(name='lightgbm-transform',
          version=version,
          description='LightGBM feature transformation binding python package',
          long_description=readme,
          install_requires=[
              'wheel',
              'numpy',
              'scipy',
              'scikit-learn!=0.22.0'
          ],
          extras_require={
              'dask': [
                  'dask[array]>=2.0.0',
                  'dask[dataframe]>=2.0.0',
                  'dask[distributed]>=2.0.0',
                  'pandas',
              ],
          },
          maintainer='Jincheng Chen',
          maintainer_email='chjinche@microsoft.com',
          zip_safe=False,
          cmdclass={
              'install': CustomInstall,
              'bdist_wheel': CustomBdistWheel,
          },
          packages=find_packages(),
          include_package_data=True,
          license='The MIT License (Microsoft)',
          url='https://github.com/microsoft/lightgbm-transform',
          classifiers=['Development Status :: 5 - Production/Stable',
                       'Intended Audience :: Science/Research',
                       'License :: OSI Approved :: MIT License',
                       'Natural Language :: English',
                       'Operating System :: MacOS',
                       'Operating System :: Microsoft :: Windows',
                       'Operating System :: POSIX',
                       'Operating System :: Unix',
                       'Programming Language :: Python :: 3',
                       'Programming Language :: Python :: 3.6',
                       'Programming Language :: Python :: 3.7',
                       'Programming Language :: Python :: 3.8',
                       'Programming Language :: Python :: 3.9',
                       'Topic :: Scientific/Engineering :: Artificial Intelligence'])

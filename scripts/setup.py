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

sys.path.insert(0, '../external_libs/LightGBM/python-package')
from setup import LIGHTGBM_OPTIONS, CustomBdistWheel, clear_path


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

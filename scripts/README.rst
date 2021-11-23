LightGBM Feature Transformation Binding Python-package
======================================================

|License| |Python Versions| |PyPI Version| |API Docs|

Installation
------------

Preparation
'''''''''''

32-bit Python is not supported. Please install 64-bit version. If you have a strong need to install with 32-bit Python, refer to `Build 32-bit Version with 32-bit Python section <#build-32-bit-version-with-32-bit-python>`__.

`setuptools <https://pypi.org/project/setuptools>`_ is needed.

Install from `PyPI <https://pypi.org/project/lightgbm-transform>`_
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

.. code:: sh

    pip install lightgbm-transform

You may need to install `wheel <https://pythonwheels.com>`_ via ``pip install wheel`` first.

Compiled library that is included in the wheel file supports **LightGBM MPI** versions out of the box.

Troubleshooting
---------------

In case you are facing any errors during the installation process, you can examine ``$HOME/LightGBM_compilation.log`` file, in which all operations are logged, to get more details about occurred problem. Also, please attach this file to the issue on GitHub to help faster indicate the cause of the error.

Refer to `FAQ <https://github.com/microsoft/LightGBM/tree/master/docs/FAQ.rst>`_.

Examples
--------

Refer to the walk through examples in `Transform tutorial <https://github.com/microsoft/lightgbm-transform/blob/main/docs/Transform-Tutorial.rst>`_.

Development Guide
-----------------

The code style of Python-package follows `PEP 8 <https://www.python.org/dev/peps/pep-0008/>`_. If you would like to make a contribution and not familiar with PEP 8, please check the PEP 8 style guide first. Otherwise, the check won't pass. Only E501 (line too long) and W503 (line break occurred before a binary operator) can be ignored.

Documentation strings (docstrings) are written in the NumPy style.

.. |License| image:: https://img.shields.io/github/license/microsoft/lightgbm.svg
   :target: https://github.com/microsoft/lightgbm-transform/blob/main/LICENSE
.. |Python Versions| image:: https://img.shields.io/pypi/pyversions/lightgbm.svg?logo=python&logoColor=white
   :target: https://pypi.org/project/lightgbm-transform
.. |PyPI Version| image:: https://img.shields.io/pypi/v/lightgbm.svg?logo=pypi&logoColor=white
   :target: https://pypi.org/project/lightgbm-transform
.. |API Docs| image:: https://readthedocs.org/projects/lightgbm/badge/?version=latest
   :target: https://lightgbm.readthedocs.io/en/latest/Python-API.html

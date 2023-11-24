Development Setup Guide for LightGBM Transform
==========================================

This guide provides instructions for setting up the development environment for LightGBM Transform on a Linux machine.

Prerequisites
-------------

* Linux operating system
* Internet connection for downloading necessary files

Setup Steps
-----------

1. **Install Docker**
   
   - Install Docker on your Linux machine by following the `instructions <https://docs.docker.com/engine/installation/linux/ubuntulinux/>`_. Ensure Docker is properly installed and running.

2. **Pull Docker Image**

   - Download the required Docker image using the command:
     ::
     
         docker pull krystal1130/lightgbm_transform_dependencies:20211109.v1

3. **Clone the Repository**

   - Clone the LightGBM Transform repository from GitHub:
     ::
     
         git clone --recursive https://github.com/microsoft/lightgbm-transform.git

4. **Mount the Repository to Docker Container**

   - Mount the cloned repository to the Docker container. Replace ``<path_to_repo>`` with your local repository path:
     ::
     
         docker run -it -v <path_to_repo>:/lightgbm-transform krystal1130/lightgbm_transform_dependencies:20211109.v1

5. **Access the Docker Container**

   - Navigate to the LightGBM Transform directory inside the Docker container:
     ::
     
         cd /lightgbm-transform

6. **Package the LightGBM Transform Python Package**

   - Compile the package and place it in the ``./compile/dist`` directory using:
     ::
     
         sh ./scripts/publish_python_package.sh

7. **Test the Package**

   - Install and test the package. Replace ``<version>`` with the actual version number:
     ::
     
         pip install --force-reinstall ./compile/dist/lightgbm_transform-<version>-py3-none-any.whl
         pip install pytest numpy scipy pandas scikit-learn
         cd ./tests
         pytest

8. **PyPI Package Publishing**

   - To request the publishing of the package to PyPI, please create an issue on `GitHub <https://github.com/microsoft/lightgbm-transform/issues>`_. Ensure that you have completed and verified all the local setup steps as outlined above before proceeding with the request.

.. Note::
   This guide assumes a basic understanding of Linux, Docker, and Git. For any issues, refer to the respective tool's documentation or community support.

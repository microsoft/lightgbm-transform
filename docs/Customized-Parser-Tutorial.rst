LightGBM Customized Parser Tutorial
===================================

The purpose of this document is to give you a tutorial on how to customize your own parser and integrate it in LightGBM to do training.
The basic methodology is to register custom parser to parser factory via reflector.

- Follow `LightGBM Parser <https://github.com/microsoft/LightGBM/blob/b0137debe6e9cc92b65ec71b0fe8a56ea213c143/include/LightGBM/dataset.h#L264>`__ interface and design your parser by implementing constructor, ``ParseOneLine``, ``NumFeatures`` functions. Then register the custom parser. See `FreeForm2Parser <../examples/freeform2_parser.cpp>`__ as an example.

- Append source file of your parser to library in `CMakeLists.txt <../CMakeLists.txt>`__. You could find that LightGBM and transform library are used as dependencies.

- See `Installation Guide <./Installation-Guide.rst>`__ for dependencies and your parser installation.

- See `Transform tutorial <./Transform-Tutorial.rst>`__ for how to use LightGBM integrated with your parser version.

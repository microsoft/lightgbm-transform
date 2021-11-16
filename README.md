# LightGBM Transformation Library

The LightGBM transformation library aims at providing a flexible and automatic way to do feature transformation when using [`LightGBM`](https://github.com/microsoft/LightGBM). Compared to separate transformation. this way has several pros:

- More efficient. Data preprocessing can go with parsing each line, and take advantage of multi-processing designed by lightgbm naturally. No need to store whole transformed data in file/memory.
- More convenient for development and iteration. Built-in transformation could keep offline and online consistent well by saved/loaded along with model.

In the repo, user could learn about:

- How to customize favorite parser by playing with LightGBM Parser interface.
- How to use [`FreeForm2Parser`](./examples/freeform2_parser.cpp), a powerful and efficient tool built in the repo, in model training. Instead of handling data yourself, user just need to prepare a feature spec which contains feature name, transform type and expression, and make slight changes in experiment iterations.

## Get Started and Documentation

- [Customized parser tutorial](./docs/Customized-Parser-Tutorial.rst).
- [Transform tutorial](./docs/Transform-Tutorial.rst).

## Contributing

This project welcomes contributions and suggestions.  Most contributions require you to agree to a
Contributor License Agreement (CLA) declaring that you have the right to, and actually do, grant us
the rights to use your contribution. For details, visit https://cla.opensource.microsoft.com.

When you submit a pull request, a CLA bot will automatically determine whether you need to provide
a CLA and decorate the PR appropriately (e.g., status check, comment). Simply follow the instructions
provided by the bot. You will only need to do this once across all repos using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or
contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

## Trademarks

This project may contain trademarks or logos for projects, products, or services. Authorized use of Microsoft 
trademarks or logos is subject to and must follow 
[Microsoft's Trademark & Brand Guidelines](https://www.microsoft.com/en-us/legal/intellectualproperty/trademarks/usage/general).
Use of Microsoft trademarks or logos in modified versions of this project must not cause confusion or imply Microsoft sponsorship.
Any use of third-party trademarks or logos are subject to those third-party's policies.

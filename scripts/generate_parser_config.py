import argparse
import json

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--class_name',
        help='The custom parser class name',
    )
    parser.add_argument(
        '--transform_file',
        help='The file path for the feature spec.',
    )
    parser.add_argument(
        '--header_file',
        help='The file path for the header file.',
        default=""
    )
    parser.add_argument(
        '--parser_config_file',
        help='The output file path for the trained LightGBM model.',
    )
    args, _ = parser.parse_known_args()
    class_name = args.class_name
    transform_file = args.transform_file
    header_file = args.header_file
    parser_config_file = args.parser_config_file
    # generate json config.
    with open(transform_file) as fin:
        transform_str = ''.join(fin.readlines())

    parser_config = {
        "className": class_name,
        "transform": transform_str
    }
    if (len(header_file) > 0):
        with open(header_file) as fin:
            header_str = ''.join(fin.readlines())
            parser_config["header"] = header_str

    with open(parser_config_file, 'w') as fout:
        json.dump(parser_config, fout)

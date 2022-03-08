import argparse
import json
import textwrap

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
    parser.add_argument(
        '--query_idx',
        type=int,
        help='The index of the query column in the origin input data.',
        default=-1
    )
    args, _ = parser.parse_known_args()
    class_name = args.class_name
    transform_file = args.transform_file
    header_file = args.header_file
    parser_config_file = args.parser_config_file
    query_idx = args.query_idx
    # generate json config.
    with open(transform_file) as fin:
        transform_str = ''.join(fin.readlines())
    
    parser_config = {
        "className": class_name,
    }
    if (len(header_file) > 0):
        with open(header_file) as fin:
            header_str = ''.join(fin.readlines())
        if (query_idx > -1):
            header_list = header_str.split('\t')
            if(query_idx >= len(header_list)):
                raise ValueError("Invalid query_idx!")
            query_name = header_list[query_idx]
            feature_cnt = transform_str.count("Input")
            query_transform = textwrap.dedent("""
                                        [Input:%d]
                                        Transform=Linear
                                        Name=%s
                                        Intercept=0
                                        Slope=1
            """) % (feature_cnt, query_name)
            transform_str = transform_str + query_transform
            print("Query_idx in transformed data is: %d" % feature_cnt)
        parser_config["transform"] = transform_str
        parser_config["header"] = header_str
    else :
        if (query_idx > -1):
            raise ValueError("No header file exists, can't auto generate query column for transformed data!")
        parser_config["transform"] = transform_str
    with open(parser_config_file, 'w') as fout:
        json.dump(parser_config, fout)

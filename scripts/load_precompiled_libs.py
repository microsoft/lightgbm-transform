import ctypes
from pathlib import Path

CUSTOM_PARSER_LIB_NAME = 'lib_custom_parser.so'
for p in ['lib_transform.so', 'lib_lightgbm.so', CUSTOM_PARSER_LIB_NAME]:
    ctypes.cdll.LoadLibrary(str(Path(__file__).resolve().parents[1] / p))

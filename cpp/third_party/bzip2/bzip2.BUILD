# vim: ft=bzl

exports_files(["LICENSE"])

cc_library(
    name = "bzip2",
    srcs = [
        "blocksort.c",
        "bzlib.c",
        "bzlib_private.h",
        "compress.c",
        "crctable.c",
        "decompress.c",
        "huffman.c",
        "randtable.c",
    ],
    hdrs = [
        "bzlib.h",
    ],
    copts = ["-w"],
    includes = ["."],
    visibility = ["//visibility:public"],
)

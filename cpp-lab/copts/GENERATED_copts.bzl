GCC_FLAGS = [
    "-std=gnu++2a",
    "-Wall",
    "-Wextra",
    "-Wcast-qual",
    "-Wconversion-null",
    "-Woverlength-strings",
    "-Wpointer-arith",
    "-Wno-unused-local-typedefs",
    "-Wno-unused-parameter",
    "-Wunused-result",
    "-Wvarargs",
    "-Wvla",
    "-Wwrite-strings",
    "-Wno-missing-field-initializers",
    "-Wno-sign-compare",
    "-msse3",
    "-msse4",
    "-msse4.1",
    "-mpclmul",
    "-fno-builtin-memcmp",
]

GCC_TEST_FLAGS = [
    "-std=gnu++2a",
    "-Wno-conversion-null",
    "-Wno-deprecated-declarations",
    "-Wno-sign-compare",
    "-Wno-unused-function",
    "-Wno-unused-parameter",
    "-Wno-unused-private-field",
]
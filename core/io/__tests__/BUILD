
cc_test(
    name = "io_file_reader_test",
    size = "small",
    srcs = ["file_reader_test.cc"],
    deps = [
        "//core/io:io_file",
        "@com_google_googletest//:gtest_main",
    ],
    data = [
        "//core/io/__tests__:data",
    ],
)

filegroup(
    name = "data",
    srcs = [
        "data.txt",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "idx_code_indexer",
    srcs = [
        "index_file.cc",
    ],
    hdrs = [
        "index_file.h",
    ],
)

cc_test(
    name = "idx_code_indexer_test",
    size = "small",
    srcs = ["index_file_test.cc"],
    env = {
        "HOME": "/Users/binhe",
    },
    deps = [
        ":idx_code_indexer",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "idx",
    srcs = [
        "main.cc",
    ],
    deps = [
        ":idx_code_indexer",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_glog//:glog",
    ],
)

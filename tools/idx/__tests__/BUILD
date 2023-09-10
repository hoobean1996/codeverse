cc_test(
    name = "idx_code_index_test",
    size = "small",
    srcs = ["code_index_test.cc"],
    env = {
        "HOME": "/Users/binhe",
    },
    deps = [
        "//tools/idx:idx_code_index",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "idx_code_index_writer_buffer_test",
    size = "small",
    srcs = ["code_index_writer_buffer_test.cc"],
    deps = [
        "//tools/idx:idx_code_index",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "idx_code_index",
    srcs = [
        "code_index.cc",
        "code_index_reader.cc",
        "code_index_writer.cc",
        "code_index_writer_buffer.cc",
        "sparse_set.cc",
    ],
    hdrs = [
        "code_index.h",
        "code_index_reader.h",
        "code_index_writer.h",
        "code_index_writer_buffer.h",
        "options.h",
        "post_entry.h",
        "sparse_set.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@com_github_google_glog//:glog",
    ],
)

cc_binary(
    name = "idx",
    srcs = [
        "main.cc",
    ],
    data = [
        ":test_main",
    ],
    deps = [
        ":idx_code_index",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_glog//:glog",
    ],
)

filegroup(
    name = "test_main",
    srcs = [
        "main.cc",
    ],
    visibility = ["//visibility:public"],
)

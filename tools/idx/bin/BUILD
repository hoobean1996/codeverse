cc_binary(
    name = "idx",
    srcs = [
        "main.cc",
    ],
    data = [
        ":test_main",
    ],
    deps = [
        "//tools/idx:idx_code_index",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_glog//:glog",
        "@com_github_jupp0r_prometheus_cpp//pull"
    ],
)

filegroup(
    name = "test_main",
    srcs = [
        "main.cc",
    ],
    visibility = ["//visibility:public"],
)

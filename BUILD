cc_binary(
    name = "libvsomeip3.so",
    linkshared = True,
    linkstatic = True,
    tags = ["same-ros-pkg-as: vsomeip3"],
    deps = [
        "//implementation",
    ],
)

cc_binary(
    name = "libvsomeip3-cfg.so.3",
    linkshared = True,
    linkstatic = True,
    visibility = ["//visibility:public"],
    deps = [
        "//implementation:configuration",
    ],
)

cc_binary(
    name = "libvsomeip3-e2e.so.3",
    linkshared = True,
    linkstatic = True,
    visibility = ["//visibility:public"],
    deps = [
        "//implementation:e2e_protection",
    ],
)

cc_binary(
    name = "libvsomeip3-sd.so.3",
    linkshared = True,
    linkstatic = True,
    visibility = ["//visibility:public"],
    deps = [
        "//implementation:service_discovery",
    ],
)

filegroup(
    name = "vsomeip3-plugins",
    srcs = [
        "libvsomeip3-cfg.so.3",
        "libvsomeip3-e2e.so.3",
        "libvsomeip3-sd.so.3",
    ],
)

cc_import(
    name = "vsomeip3_import",
    shared_library = ":libvsomeip3.so",
    tags = ["same-ros-pkg-as: vsomeip3"],
    deps = ["//interface"],
)

cc_library(
    name = "vsomeip3",
    data = [":vsomeip3-plugins"],
    linkstatic = True,  # no object files
    visibility = ["//visibility:public"],
    deps = [":vsomeip3_import"],
)

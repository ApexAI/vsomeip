cc_binary(
    name = "libvsomeip3.so",
    linkshared = True,
    linkstatic = True,
    deps = [
        "//implementation",
    ],
)

cc_binary(
    name = "libvsomeip3-cfg.so.3",
    linkshared = True,
    linkstatic = True,
    deps = [
        "//implementation:configuration",
    ],
    visibility = ["//test:__subpackages__"],
)

cc_binary(
    name = "libvsomeip3-e2e.so.3",
    linkshared = True,
    linkstatic = True,
    deps = [
        "//implementation:e2e_protection",
    ],
)

cc_binary(
    name = "libvsomeip3-sd.so.3",
    linkshared = True,
    linkstatic = True,
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

cc_library(
    name = "vsomeip3",
    srcs = [":libvsomeip3.so"],
    deps = ["//interface"],
    data = [":vsomeip3-plugins"],
    visibility = ["//visibility:public"],
    linkstatic = True, # no object files
)

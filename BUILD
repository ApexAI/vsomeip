cc_binary(
    name = "libvsomeip3.so",
    linkshared = True,
    linkstatic = True,
    visibility = ["//visibility:public"],
    deps = [
        "//implementation",
    ],
)

cc_binary(
    name = "libvsomeip3-cfg.so.3",
    srcs = [
        "libvsomeip3.so",
    ],
    linkopts = [
        "-Wl,-rpath=\\$$ORIGIN:\\$$ORIGIN/../implementation:\\$$ORIGIN/../../implementation",
    ],
    linkshared = True,
    linkstatic = True,
    visibility = ["//visibility:public"],
    deps = [
        "//implementation:configuration",
    ],
)

cc_binary(
    name = "libvsomeip3-e2e.so.3",
    srcs = [
        "libvsomeip3.so",
    ],
    linkopts = [
        "-Wl,-rpath=\\$$ORIGIN:\\$$ORIGIN/../implementation:\\$$ORIGIN/../../implementation",
    ],
    linkshared = True,
    linkstatic = True,
    visibility = ["//visibility:public"],
    deps = [
        "//implementation:e2e_protection",
    ],
)

cc_binary(
    name = "libvsomeip3-sd.so.3",
    srcs = [
        "libvsomeip3.so",
    ],
    linkopts = [
        "-Wl,-rpath=\\$$ORIGIN:\\$$ORIGIN/../implementation:\\$$ORIGIN/../../implementation",
    ],
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
    visibility = ["//visibility:public"],
)
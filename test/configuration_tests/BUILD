filegroup(
    name = "configuration-test-files",
    srcs = [
        "configuration-test.json",
        "configuration-test-deprecated.json",
    ],
)

cc_test(
    name = "configuration-test",
    srcs = [
        "configuration-test.cpp",
        "//:libvsomeip3-cfg.so.3",
    ],
    data = [
        ":configuration-test-files",
    ],
    defines = ["VSOMEIP_CLEAN_INCLUDES"],
    deps = [
        "//:vsomeip3",
        "//implementation:includes",
        "@googletest//:gtest",
    ],
)

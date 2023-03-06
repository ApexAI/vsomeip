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
        "//:libvsomeip3.so",
        "//:libvsomeip3-cfg.so.3",
    ],
    data = [
        ":configuration-test-files",
        "//:vsomeip3-plugins",
    ],
    defines = ["VSOMEIP_CLEAN_INCLUDES"],
    deps = [
        "//interface",
        "//implementation:includes",
        "@googletest//:gtest",
    ],
)

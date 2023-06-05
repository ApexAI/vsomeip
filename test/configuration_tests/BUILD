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
    target_compatible_with = [
        # FIXME: Test does not build for QNX
        "@platforms//os:linux",
    ],
    deps = [
        "//:vsomeip3",
        "//implementation:includes",
        "@boost//:asio",
        "@googletest//:gtest",
    ],
)

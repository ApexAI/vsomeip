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
    ],
    defines = [ "VSOMEIP_CLEAN_INCLUDES" ],
    data = [":configuration-test-files"],
    deps = [
        "//implementation:vsomeip3",
        "//implementation:vsomeip3-testing",
        "@googletest//:gtest",
    ],
)
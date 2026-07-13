cc_test(
    name = "routing_manager_tests",
    srcs = glob([
        "*.cpp",
        "*.hpp",
        "mocks/*.cpp",
        "mocks/*.hpp",
    ]),
    copts = ["-Wno-error"],
    deps = [
        "//implementation",
        "//implementation:configuration",
        "//implementation:service_discovery",
        "@boost//:headers",
        "@googletest//:gtest_main",
    ],
)

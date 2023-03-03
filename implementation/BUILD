load("@vsomeip//bazel:cmake_like_configure_file.bzl", "cmake_like_configure_file")
load("@vsomeip//bazel:version.bzl", _vsomeip_version_str = "vsomeip_version_str")

cmake_like_configure_file(
    name = "config",
    src = "configuration/include/internal.hpp.in",
    out = "configuration/include/internal_config.hpp",
    config = {
        "DEFAULT_CONFIGURATION_FILE": "/etc/vsomeip.json",
        "DEFAULT_CONFIGURATION_FOLDER": "/etc/vsomeip",
        "VSOMEIP_BASE_PATH": "/tmp",
        "VSOMEIP_MAJOR_VERSION": "3",
        "VSOMEIP_UNICAST_ADDRESS": "127.0.0.1",
        "VSOMEIP_DIAGNOSIS_ADDRESS": "0x01",
        "VSOMEIP_ROUTING_READY_MESSAGE": "SOME/IP routing ready.",
    },
)

cc_library(
    name = "helper",
    hdrs = glob(
        [
            "helper/1.74/**/*.hpp",
            "helper/1.74/**/*.ipp",
        ],
    ),
    strip_include_prefix = "helper/1.74",
    deps = [
        "@boost//:headers",
    ],
)

cc_library(
    name = "includes",
    hdrs = glob(
        [
            "*/include/**/*.hpp",
        ],
    ) + [":config"],
    includes = glob(
        [
            "*/include",
        ],
    ) + ["message"],
    visibility = [
        ":__subpackages__",
        "//test:__subpackages__",
    ],
)

cc_library(
    name = "configuration",
    srcs = glob(
        [
            "configuration/src/*.cpp",
        ],
    ),
    visibility = ["//visibility:public"],
    deps = [
        ":helper",
        ":includes",
        "//interface",
        "@boost//:filesystem",
    ],
    alwayslink = True,
)

cc_library(
    name = "service_discovery",
    srcs = glob(
        [
            "service_discovery/src/*.cpp",
        ],
    ),
    visibility = ["//visibility:public"],
    deps = [
        ":helper",
        ":includes",
        "//interface",
    ],
    alwayslink = True,
)

cc_library(
    name = "e2e_protection",
    srcs = glob(
        [
            "e2e_protection/src/*.cpp",
        ],
    ),
    visibility = ["//visibility:public"],
    deps = [
        ":helper",
        ":includes",
        "//interface",
    ],
    alwayslink = True,
)

cc_library(
    name = "implementation",
    srcs = glob(
        [
            "endpoints/src/*.cpp",
            "logger/src/*.cpp",
            "tracing/src/*.cpp",
            "message/src/*.cpp",
            "plugin/src/*.cpp",
            "routing/src/*.cpp",
            "runtime/src/*.cpp",
            "security/src/*.cpp",
            "utility/src/*.cpp",
        ],
    ),
    defines = [
        "WITHOUT_SYSTEMD",
        "VSOMEIP_VERSION=\\\"%s\\\"" % _vsomeip_version_str(),
    ],
    linkopts = [
        "-lpthread",
        "-ldl",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":helper",
        ":includes",
        "//interface",
    ],
    alwayslink = True,
)

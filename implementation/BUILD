load("@vsomeip//bazel:cmake_like_configure_file.bzl", "cmake_like_configure_file")

VSOMEIP_NAME = "vsomeip3"

VSOMEIP_COMPAT_NAME = "vsomeip"

cmake_like_configure_file(
    name = VSOMEIP_NAME + "-config",
    src = "configuration/include/internal.hpp.in",
    out = "configuration/include/internal_config.hpp",
    config = {
        "DEFAULT_CONFIGURATION_FILE": "/etc/vsomeip.json",
        "DEFAULT_CONFIGURATION_FOLDER": "/etc/vsomeip",
        "VSOMEIP_BASE_PATH": "/tmp",
        "VSOMEIP_MAJOR_VERSION" : "3",
        "VSOMEIP_UNICAST_ADDRESS": "127.0.0.1",
        "VSOMEIP_DIAGNOSIS_ADDRESS": "0x01",
        "VSOMEIP_ROUTING_READY_MESSAGE": "SOME/IP routing ready.",
    },
)

cc_library(
    name = VSOMEIP_NAME + "-helper",
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
    name = VSOMEIP_NAME + "-includes",
    hdrs = glob(
        [
            "*/include/**/*.hpp",
        ],
    ) + [":" + VSOMEIP_NAME + "-config"],
    includes = glob(
        [
            "*/include",
        ],
    ),
)

cc_binary(
    name = "lib" + VSOMEIP_NAME + "-cfg" + ".so.3",
    srcs = glob(
        [
            "configuration/src/*.cpp",
        ],
    ),
    copts = ["-fpic"],
    linkshared = True,
    linkstatic = False,
    visibility = ["//visibility:public"],
    deps = [
        "//interface:vsomeip3-interface",
        ":" + VSOMEIP_NAME + "-helper",
        ":" + VSOMEIP_NAME + "-includes",
        ":" + VSOMEIP_NAME,
        "@boost//:filesystem",
    ],
)

cc_binary(
    name = "lib" + VSOMEIP_NAME + "-sd" + ".so.3",
    srcs = glob(
        [
            "service_discovery/src/*.cpp",
        ],
    ),
    copts = ["-fpic"],
    linkshared = True,
    linkstatic = False,
    visibility = ["//visibility:public"],
    deps = [
        "//interface:vsomeip3-interface",
        ":" + VSOMEIP_NAME + "-helper",
        ":" + VSOMEIP_NAME + "-includes",
    ],
)

cc_binary(
    name = "lib" + VSOMEIP_NAME + "-e2e" + ".so.3",
    srcs = glob(
        [
            "e2e_protection/src/*.cpp",
        ],
    ),
    copts = ["-fpic"],
    linkshared = True,
    linkstatic = False,
    visibility = ["//visibility:public"],
    deps = [
        "//interface:vsomeip3-interface",
        ":" + VSOMEIP_NAME + "-helper",
        ":" + VSOMEIP_NAME + "-includes",
    ],
)

cc_library(
    name = VSOMEIP_NAME,
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
        #"VSOMEIP_ENABLE_MULTIPLE_ROUTING_MANAGERS",
    ],
    linkopts = [
        "-Wl,-rpath=\\$$ORIGIN/../implementation:\\$$ORIGIN/../../implementation",
        "-lpthread",
        "-ldl",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//interface:vsomeip3-interface",
        ":" + VSOMEIP_NAME + "-helper",
        ":" + VSOMEIP_NAME + "-includes",
    ],
)

cc_library(
    name = VSOMEIP_NAME + "-testing",
    srcs = glob(
        [
            "plugin/src/plugin_manager_impl.cpp",
            "configuration/src/*.cpp",
        ],
    ),
    hdrs = glob(
        [
            "**/*.hpp",
        ],
    ),
    include_prefix = ".",
    visibility = ["//visibility:public"],
    deps = [
        "//interface:vsomeip3-interface",
        ":" + VSOMEIP_NAME + "-helper",
        ":" + VSOMEIP_NAME + "-includes",
        "@boost//:filesystem",
    ],
)

cc_library(
    name = VSOMEIP_COMPAT_NAME,
    srcs = glob(
        [
            "compat/logging/src/*.cpp",
            "compat/message/src/*.cpp",
            "compat/runtime/src/*.cpp",
        ],
    ),
    hdrs = glob(
        [
            "compat/*/include/**/*.hpp",
        ],
    ),
    include_prefix = "compat/message/include",
    includes = glob(
        [
            "compat/*/include",
        ],
    ),
    visibility = ["//visibility:public"],
    deps = [
        "//interface:vsomeip3-interface",
        ":" + VSOMEIP_NAME + "-helper",
        ":" + VSOMEIP_NAME + "-includes",
    ],
)

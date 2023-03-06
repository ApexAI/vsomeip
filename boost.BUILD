load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "headers",
    hdrs = glob(
        [
            "boost/**",
        ],
    ),
    local_defines = ["BOOST_ALL_NO_LIB"],
    include_prefix = ".",
)

cc_library(
    name = "asio",
    srcs = glob(
        [
            "libs/asio/src/**",
        ],
    ),
    linkopts = select({
        "@platforms//os:linux": ["-lpthread"],
        "@platforms//os:windows": [],
    }),
    deps = [
        ":headers",
    ],
)

cc_library(
    name = "_atomic_detail",
    hdrs = ["libs/atomic/src/lock_pool_init1.ipp"],
    strip_include_prefix = "libs/atomic/src",
    visibility = ["//visibility:private"],
)

cc_library(
    name = "atomic",
    srcs = glob(
        [
            "libs/atomic/src/**",
        ],
        exclude = [
            "libs/atomic/src/lock_pool_init1.ipp",
            "libs/atomic/src/wait_ops_windows.cpp",
        ],
    ) + select(
        {
            "@platforms//os:linux": [],
            "@platforms//os:windows": ["libs/atomic/src/wait_ops_windows.cpp"],
        },
    ),
    copts = [
        "-Ilibs/atomic/src",
    ],
    implementation_deps = [
        ":_atomic_detail",
    ],
    deps = [
        ":headers",
        ":thread",
    ],
)

cc_library(
    name = "chrono",
    srcs = glob(
        [
            "libs/chrono/src/**",
        ],
    ),
    deps = [
        ":headers",
    ],
)

cc_library(
    name = "program_options",
    srcs = glob(
        [
            "libs/program_options/src/**",
        ],
    ),
    deps = [
        ":headers",
    ],
)

cc_library(
    name = "system",
    srcs = glob(
        [
            "libs/system/src/**",
        ],
    ),
    deps = [
        ":headers",
    ],
)

cc_library(
    name = "_thread_detail",
    hdrs = select({
        "@platforms//os:linux": ["libs/thread/src/pthread/once_atomic.cpp"],
    }),
    strip_include_prefix = "libs/thread/src/pthread",
    visibility = ["//visibility:private"],
)

cc_library(
    name = "thread",
    srcs = glob(
        [
            "libs/thread/src/*.cpp",
        ],
    ) + select({
        "@platforms//os:linux": [
            "libs/thread/src/pthread/once.cpp",
            "libs/thread/src/pthread/thread.cpp",
        ],
        "@platforms//os:windows": glob([
            "libs/thread/src/win32/*.cpp",
        ]),
    }),
    implementation_deps = [
        ":_thread_detail",
    ],
    linkopts = select({
        "@platforms//os:linux": ["-lpthread"],
        "@platforms//os:windows": [],
    }),
    deps = [
        ":headers",
    ],
)

cc_library(
    name = "filesystem",
    srcs = glob(
        [
            "libs/filesystem/src/**",
        ],
    ),
    deps = [
        ":headers",
    ],
)

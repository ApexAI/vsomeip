load("@apex//tools/bazel/rules_ros_pkg:defs.bzl", "ros_pkg")

cc_shared_library(
    name = "vsomeip3_shared",
    shared_lib_name = "libvsomeip3.so",
    tags = ["same-ros-pkg-as: vsomeip3"],
    user_link_flags = select({
        "@platforms//os:linux": [
            "-lpthread",
            "-Wl,-rpath,'$ORIGIN/../../external/vsomeip/:$ORIGIN/../../../external/vsomeip/'",  # Adds relative search path
        ],
        "//conditions:default": [],
    }),
    # Disabled due to linking problem when used as an external repository with sanitizers enabled.
    #user_link_flags = [
    #    "-Wl,--no-undefined",
    #],
    deps = [
        "//implementation",
    ],
)

cc_import(
    name = "vsomeip3_import",
    shared_library = ":vsomeip3_shared",
    tags = ["same-ros-pkg-as: vsomeip3"],
    visibility = ["//visibility:public"],
    deps = ["//interface"],
)

# interface library, use this target to depend on vsomeip
cc_library(
    name = "vsomeip3",
    data = [":vsomeip3_shared"],
    linkopts = select({
        "@platforms//os:linux": ["-lpthread"],
        "//conditions:default": [],
    }),
    linkstatic = True,  # no object files
    visibility = ["//visibility:public"],
    deps = [
        ":vsomeip3_import",
    ],
)

ros_pkg(
    name = "vsomeip_pkg",
    cc_libraries = [
        ":vsomeip3",
    ],
    description = "CMake shim over the https://github.com/COVESA/vsomeip.git",
    license = "Apache License 2.0",
    maintainer_email = "support@apex.ai",
    maintainer_name = "Apex.AI",
    pkg_name = "vsomeip",
    version = "3.3.0",
    visibility = ["//visibility:public"],
    deps = [
        "@boost//:boost_pkg",
    ],
)

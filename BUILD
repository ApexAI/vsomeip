cc_shared_library(
    name = "vsomeip3_shared",
    shared_lib_name = "libvsomeip3.so",
    tags = ["same-ros-pkg-as: vsomeip3"],
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

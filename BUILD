cc_shared_library(
    name = "vsomeip3_shared",
    shared_lib_name = "libvsomeip3.so",
    tags = [
        "Use short library name in install space",
        "same-ros-pkg-as: vsomeip3",
    ],
    # Disabled due to linking problem when used as an external repository with sanitizers enabled.
    #user_link_flags = [
    #    "-Wl,--no-undefined",
    #],
    deps = [
        "//implementation",
    ],
)

cc_shared_library(
    name = "vsomeip3_config_plugin",
    dynamic_deps = [
        ":vsomeip3_shared",
    ],
    shared_lib_name = "libvsomeip3-cfg.so.3",
    tags = [
        "Use short library name in install space",
        "same-ros-pkg-as: vsomeip3",
    ],
    # Disabled due to linking problem when used as an external repository with sanitizers enabled.
    #user_link_flags = [
    #    "-Wl,--no-undefined",
    #],
    deps = [
        "//implementation:configuration",
    ],
)

cc_shared_library(
    name = "vsomeip3_sd_plugin",
    dynamic_deps = [
        ":vsomeip3_shared",
    ],
    shared_lib_name = "libvsomeip3-sd.so.3",
    tags = [
        "Use short library name in install space",
        "same-ros-pkg-as: vsomeip3",
    ],
    # Disabled due to linking problem when used as an external repository with sanitizers enabled.
    #user_link_flags = [
    #    "-Wl,--no-undefined",
    #],
    deps = [
        "//implementation:service_discovery",
    ],
)

cc_import(
    name = "vsomeip3_import",
    shared_library = ":vsomeip3_shared",
    tags = ["same-ros-pkg-as: vsomeip3"],
    deps = [
        "//interface",
    ],
)

# interface library, use this target to depend on vsomeip
cc_library(
    name = "vsomeip3",
    data = [
        ":vsomeip3_config_plugin",
        ":vsomeip3_sd_plugin",
    ],
    linkstatic = True,  # no object files
    visibility = ["//visibility:public"],
    deps = [
        ":vsomeip3_import",
    ],
)

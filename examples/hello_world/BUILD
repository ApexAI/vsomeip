cc_library(
    name = "vsomeip_hello_world_service",
    hdrs = ["hello_world_service.hpp"],
    include_prefix = ".",
)

cc_library(
    name = "vsomeip_hello_world_client",
    hdrs = ["hello_world_client.hpp"],
    include_prefix = ".",
)

cc_binary(
    name = "hello_world_service",
    srcs = [
        "hello_world_service_main.cpp",
        "//:libvsomeip3.so"
    ],
    deps = [
        ":vsomeip_hello_world_service",
        "//interface",
    ],
    data = [
        "//:vsomeip3-plugins"
    ],
    linkopts = [
        "-Wl,-rpath=\\$$ORIGIN/../..,--disable-new-dtags",
    ],
)

cc_binary(
    name = "hello_world_client",
    srcs = [
        "hello_world_client_main.cpp",
        "//:libvsomeip3.so"
    ],
    deps = [
        ":vsomeip_hello_world_client",
        "//interface",
    ],
    data = [
        "//:vsomeip3-plugins"
    ],
    linkopts = [
        "-Wl,-rpath=\\$$ORIGIN/../..,--disable-new-dtags",
    ],
)

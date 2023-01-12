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
    srcs = ["hello_world_service_main.cpp"],
    deps = [
        ":vsomeip_hello_world_service",
        "//implementation:vsomeip3",
        #"//implementation:vsomeip3-cfg",
    ],
)

cc_binary(
    name = "hello_world_client",
    srcs = ["hello_world_client_main.cpp"],
    deps = [
        ":vsomeip_hello_world_client",
        "//implementation:vsomeip3",
        #"//implementation:vsomeip3-cfg",
    ],
)

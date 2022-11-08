load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "hello-world",
    srcs = ["hello-world.cc"],
    deps = [
        ":fmt",
    ],
)

cc_library(
    name = "fmt",
    srcs = ["format.cc"],
    hdrs = [
        "color.h",
        "core.h",
        "format.h",
        "format-inl.h",
    ],
)

load("@rules_cc//cc:defs.bzl", "cc_binary")

# Headers
cc_library(
    name = "LoggingTypes",
    srcs = ["LoggingTypes.hh"],
)

cc_library(
    name = "Macros",
    srcs = ["Macros.hh"],
)

# Libraries
cc_library(
    name = "Logging",
    srcs = ["Logging.cc"],
    hdrs = ["Logging.hh"],
)

cc_library(
    name = "Overrides",
    srcs = ["Overrides.cc"],
)

cc_library(
    name = "Settings",
    srcs = ["Settings.cc"],
)

cc_library(
    name = "Utils",
    srcs = ["Utils.cc"],
)

# Executables
cc_binary(
    name = "LoggingDemo",
    srcs = ["LoggingDemo.cc"],
)

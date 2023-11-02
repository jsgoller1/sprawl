### General vars
SHELL:=/bin/bash
DIR:=$(shell pwd)
MAKEFILE_DIR:=$(DIR)/makefiles
BIN_DIR:=$(DIR)/bin
DEP_DIR:=$(DIR)/deps
LOG_DIR:=$(DIR)/logs
PLATFORM:=$(shell uname)
PROJECT_NAME:=sprawl
ENGINE_BIN:=$(BIN_DIR)/$(PROJECT_NAME)

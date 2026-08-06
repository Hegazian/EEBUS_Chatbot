############################################################################
# Makefile for ICCPDv2 KEO stack
# v.1.0.0.0
# Copyright bebro electronic GmbH 2016
############################################################################
export SHELL := /bin/bash
COMP_DIR := $(shell pwd)
BUILD_ENTRY_POINT := $(COMP_DIR)/../../../build
include ${BUILD_ENTRY_POINT}/tools.min
include ${BUILD_ENTRY_POINT}/function.min
ARCH ?= localhost

ifeq ($(ARCH),arm)
	CMAKE_OPTIONS := -DSDK_BASE=$(COMP_DIR)/../../../opt/bebro-pladev/sysroots -DCMAKE_INSTALL_PREFIX=$(COMP_DIR)/arm -DKEO_SPINE_DATAGRAM_ROOT=$(COMP_DIR)/arm/ -DCMAKE_TOOLCHAIN_FILE=$(COMP_DIR)/bebro-2.2.3.cmake -DCMAKE_BUILD_TYPE=release
else
	CMAKE_OPTIONS := -DCMAKE_INSTALL_PREFIX=$(COMP_DIR)/localhost -DKEO_SPINE_DATAGRAM_ROOT=$(COMP_DIR)/localhost -DCMAKE_BUILD_TYPE=release
endif

define CALL_CMAKE
	mkdir -p /tmp/$1/$2/cmake_build &&\
	pushd /tmp/$1/$2/cmake_build &&\
	cmake $3 $(CMAKE_OPTIONS) &&\
	make -j$(NPROCS) install
endef

all: datagram spine
	echo "done";

datagram spine:
	$(call CALL_CMAKE,$@,$(ARCH),$(COMP_DIR)/src/$@)


clean:
	rm -rvf $(COMP_DIR)/$(ARCH)/*
	rm -rvf $(COMP_DIR)/src/datagram/build/*
	rm -rvf $(COMP_DIR)/src/spine/build/*
	rm -rvf /tmp/datagram/$(ARCH)/cmake_build
	rm -rvf /tmp/spine/$(ARCH)/cmake_build


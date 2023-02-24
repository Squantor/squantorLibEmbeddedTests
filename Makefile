# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Generic project makefile
# Heavily inspired by: https://github.com/bronson/makefile-death
#
# Version: 20230106

# User definable settings are here

# Define a default project to compile, replace with wanted project
PROJECT ?= libEmbeddedTests
# Verbose output?
VERBOSE ?= 0


# --- nothing user definable below ---

# --- useful variables ---

DATESTRING := $(shell date +%Y%m%d%H%M%S)
# get the root directory of the build, used below for reproducable builds
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
# root paths for various outputs
DOC_ROOT := doxyOutput
BIN_ROOT := bin
OBJ_ROOT := build

# Verbosity handling
ifeq ($(VERBOSE),1)
  C = 
  U = @true
else
  C = @
  U = @echo
endif

# --- sane defaults ---
.DEFAULT_GOAL := all
SHELL := bash
# .ONESHELL # commented out as it is incompatible in how we do verbosity
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules

# change recipe prefix to something more sensible then TAB
ifeq ($(origin .RECIPEPREFIX), undefined)
  $(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
endif
.RECIPEPREFIX = >

# collect all libraries
LIBRARIES :=
ifneq ("$(wildcard libraries.mak)","")
  include libraries.mak
endif

# collect all project information
ifndef PROJECT
  $(error no PROJECT defined!)
endif
PROJECTS :=
ifneq ("$(wildcard projects.mak)","")
  include projects.mak
endif
# check if PROJECT exists in PROJECTS
ifeq (, $(filter $(PROJECT),$(PROJECTS)))
  $(error Unknown project $(PROJECT)!)
endif

# check project library definitions
INVALID_LIBS := $(filter-out $(LIBRARIES),$($(PROJECT)_LIBS))
ifneq ($(INVALID_LIBS),)
	$(error invalid project libraries in $(PROJECT)_LIBS: $(INVALID_LIBS))
endif

# Target definition handling
ifndef $(PROJECT)_TARGET
  $(error Target is not defined!)
else
include targets/$($(PROJECT)_TARGET).mak
endif

# --- build engine ---

# --- collect all files ---
# TODO, make INCLUDES and FILES generated here, dont let any library or project touch these
INCLUDES += $(foreach library,$($(PROJECT)_LIBS),$($(library)_LIB_INCLUDES))
# FILES += $(foreach file,$($(PROJECT)_LIBS),$($(file)_LIB_FILES))
INCLUDES += $($(PROJECT)_INCLUDES)
FILES += $($(PROJECT)_FILES)

# --- configuration management --
# load first config as default configuration
CONFIG ?= $(firstword $(CONFIGS))
# check if it is a valid configuration
ifeq (, $(filter $(CONFIG),$(CONFIGS)))
  $(error Unknown configuration $(CONFIG)!)
endif

# transform configuration specific variables to variables used by the build
COPYVARS := FILES CFLAGS CXXFLAGS DEFINES
$(foreach V,$(COPYVARS),$(eval $(V) += $$($(V)_$(CONFIG))))
# specific handling for linker script
LDFLAGS += $(LDSCRIPT)
# add defines to flags
CFLAGS += $(DEFINES)
CXXFLAGS += $(DEFINES)
ASMFLAGS += $(DEFINES)
# substitute absolute paths with relative ones
CFLAGS += -fdebug-prefix-map=$(ROOT_DIR)=.
CXXFLAGS += -fdebug-prefix-map=$(ROOT_DIR)=.
ASMFLAGS += -fdebug-prefix-map=$(ROOT_DIR)=.

# for a multi project build pipeline
ifdef PROJECT
DOC_PATH := $(DOC_ROOT)/$(PROJECT)
BIN_PATH := $(BIN_ROOT)/$(PROJECT)/$(CONFIG)
OBJ_PATH := $(OBJ_ROOT)/$(PROJECT)/$(CONFIG)
EXECUTABLE := $(BIN_PATH)/$(PROJECT).elf
# PROJECT_ROOT is generated by the 
SIZELOG_PATH := $($(PROJECT)_PROJECT_ROOT)/
endif

# create file creation prerequisites 
BINDEPS := $(OBJ_PATH)/build-tag $(BIN_PATH)/build-tag
DOCDEPS := $(DOC_PATH)/build-tag
# create lists of prerequisites for the project
PROJECT_OBJECTS := $(addprefix $(OBJ_PATH)/, $(addsuffix .o,$(FILES)))
OBJECTS := $(addprefix $(OBJ_PATH)/, $(addsuffix .o,$(FILES)))
DEPS := $(OBJECTS:.o=.d)
# create lists of prerequisites for each library
LIBRARY_FILES := $(foreach library,$($(PROJECT)_LIBS),$(BIN_PATH)/$(library).a)
$(foreach library,$($(PROJECT)_LIBS),$(eval OBJECTS += $(addprefix $(OBJ_PATH)/, $(addsuffix .o,$($(library)_LIB_FILES)))))
$(foreach library,$($(PROJECT)_LIBS),$(eval $(library)_OBJECTS += $(addprefix $(OBJ_PATH)/, $(addsuffix .o,$($(library)_LIB_FILES)))))
$(foreach library,$($(PROJECT)_LIBS),$(eval DEPS := $($(library)_OBJS:.o=.d)))

all: $(BINDEPS) $(EXECUTABLE)

.PHONY: all

-include $(DEPS)

$(DOC_PATH)/build-tag:
> $(C)$(MKDIR) -p $(DOC_PATH)
> $(C)$(TOUCH) $@

$(BIN_PATH)/build-tag:
> $(C)$(MKDIR) -p $(BIN_PATH)
> $(C)$(TOUCH) $@

$(OBJ_PATH)/build-tag:
> $(C)$(MKDIR) -p $(OBJ_PATH)
> $(C)$(TOUCH) $@
ifdef $(PROJECT)_PREBUILD_SCRIPT
> $(U) "PRE $($(PROJECT)_PREBUILD_SCRIPT)"
> $(SHELL) $($(PROJECT)_PREBUILD_SCRIPT)
endif

doc: $(DOCDEPS)
> $(C)$(MKDIR) -p $(DOC_PATH)
> $(C)( cat doxygen/Doxyfile ; echo "@INCLUDE = $(PROJECT)/$(PROJECT).doxy" ) | doxygen -
.PHONY: doc

$(EXECUTABLE): $(OBJECTS) $(LIBRARY_FILES)
> $(U) "Linking $(EXECUTABLE)"
> $(C)$(TOOLCHAIN_PREFIX)$(CXX_COMPILER) $(LDFLAGS) $(PROJECT_OBJECTS) -Xlinker -Map="$@.map" -o $@ $(LIBRARY_FILES) $(TARGET_LIBRARIES)
> $(C)date >> $(SIZELOG_PATH)size$(CONFIG).log
> $(C)$(TOOLCHAIN_PREFIX)$(SIZE) $@ >> $(SIZELOG_PATH)size$(CONFIG).log
> $(C)$(TOOLCHAIN_PREFIX)$(OBJCOPY) -R .stack -O binary $@ $(BIN_PATH)/$(PROJECT).bin
> $(C)$(TOOLCHAIN_PREFIX)$(OBJDUMP) -h -S "$@" > "$(BIN_PATH)/$(PROJECT).lss"
ifdef $(PROJECT)_POSTBUILD_SCRIPT
> $(U) "POST $($(PROJECT)_POSTBUILD_SCRIPT)"
> $(SHELL) $($(PROJECT)_POSTBUILD_SCRIPT)
endif

$(BIN_PATH)/%.a: $(OBJECTS)
> $(U) "AR  $(basename $(notdir $@))"
> $(C)$(TOOLCHAIN_PREFIX)$(AR) rs $@ $($*_OBJECTS)

$(OBJ_PATH)/%.c.o: %.c
> $(U) "C   $(basename $(notdir $@))"
> $(C)$(MKDIR) -p $(dir $@) 
> $(C)$(TOOLCHAIN_PREFIX)$(C_COMPILER) $(CFLAGS) $(INCLUDES) -MP -MMD -c -o $@ $<

$(OBJ_PATH)/%.cpp.o: %.cpp
> $(U) "C++ $(basename $(notdir $@))"
> $(C)$(MKDIR) -p $(dir $@) 
> $(C)$(TOOLCHAIN_PREFIX)$(CXX_COMPILER) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c -o $@ $<

$(OBJ_PATH)/%.S.o: %.S
> $(U) "ASM $(basename $(notdir $@))"
> $(C)$(MKDIR) -p $(dir $@) 
> $(C)$(TOOLCHAIN_PREFIX)$(C_COMPILER) $(ASMFLAGS) $(INCLUDES) -MP -MMD -c -o $@ $<

clean: $(BINDEPS) $(DOCDEPS)
> $(U) "Cleaning"
> $(C)$(RM) -rf $(BIN_ROOT)
> $(C)$(RM) -rf $(OBJ_ROOT)
> $(C)$(RM) -rf $(DOC_ROOT)
.PHONY: clean

# utility rules
ifneq ("$(wildcard makefiles/util.mak)","")
include makefiles/util.mak
endif

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging
print-%: ; @echo $*=$($*)
.Phony: print-%

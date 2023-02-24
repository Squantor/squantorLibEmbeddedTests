# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20230101

# current makefile base dir relative to Makefile
PROJ_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# project settings
NAME := libEmbeddedTests
$(NAME)_TARGET := PC
$(NAME)_DEFINES := -DMINUNIT_MAX_TESTS=1000
$(NAME)_LIBS := squantorMinUnit squantorLibEmbedded
$(NAME)_FILES := $(PROJ_DIR)/src/main.cpp \
$(PROJ_DIR)/src/test_array.cpp \
$(PROJ_DIR)/src/mock_datastreamchar.c \
$(PROJ_DIR)/src/test_queue_char.c \
$(PROJ_DIR)/src/test_queue_string.c \
$(PROJ_DIR)/src/test_print.c \
$(PROJ_DIR)/src/test_cmdprompt.c \
$(PROJ_DIR)/src/test_command_mini.c \
$(PROJ_DIR)/src/test_dsputs.c \
$(PROJ_DIR)/src/test_dsread.c \
$(PROJ_DIR)/src/test_dswrite.c \
$(PROJ_DIR)/src/test_dummy.c \
$(PROJ_DIR)/src/test_parse_ansi.c \
$(PROJ_DIR)/src/test_prompt_mini.c \
$(PROJ_DIR)/src/test_ringbuf_macro.c \
$(PROJ_DIR)/src/test_moving_average.c \
$(PROJ_DIR)/src/test_moving_average.cpp \
$(PROJ_DIR)/src/test_ringbuf.cpp \
$(PROJ_DIR)/src/test_atomic.cpp \
$(PROJ_DIR)/src/test_sharp_memlcd.cpp \
$(PROJ_DIR)/src/test_font8x8.cpp \
$(PROJ_DIR)/src/test_bitzoom.c \
$(PROJ_DIR)/src/test_pulse_density.c \
$(PROJ_DIR)/src/test_pulse_density.cpp \
$(PROJ_DIR)/src/test_bitblit1d.cpp \
$(PROJ_DIR)/src/test_rmw.cpp \
$(PROJ_DIR)/src/test_bitblit2d.cpp \
$(PROJ_DIR)/src/test_elementpack.cpp \
$(PROJ_DIR)/src/test_bitblit2dsmall.cpp
$(NAME)_INCLUDES := -I$(PROJ_DIR)/inc
$(NAME)_PREBUILD_SCRIPT := $(PROJ_DIR)/prebuild.sh
$(NAME)_POSTBUILD_SCRIPT := $(PROJ_DIR)/postbuild.sh

# --- nothing user definable below ---
PROJECTS += $(NAME)
$(NAME)_PROJECT_ROOT := $(PROJ_DIR)

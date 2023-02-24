# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# project settings
#
# Version: 20200722

# additional library includes
include squantorMinUnit/squantorMinUnit.mak
include squantorLibEmbedded/squantorLibEmbedded.mak

# project settings
TARGET = PC

# project sources
FILES += $(PROJECT)/src/main.cpp \
$(PROJECT)/src/test_array.cpp \
$(PROJECT)/src/mock_datastreamchar.c \
$(PROJECT)/src/test_queue_char.c \
$(PROJECT)/src/test_queue_string.c \
$(PROJECT)/src/test_print.c \
$(PROJECT)/src/test_cmdprompt.c \
$(PROJECT)/src/test_command_mini.c \
$(PROJECT)/src/test_dsputs.c \
$(PROJECT)/src/test_dsread.c \
$(PROJECT)/src/test_dswrite.c \
$(PROJECT)/src/test_dummy.c \
$(PROJECT)/src/test_parse_ansi.c \
$(PROJECT)/src/test_prompt_mini.c \
$(PROJECT)/src/test_ringbuf_macro.c \
$(PROJECT)/src/test_moving_average.c \
$(PROJECT)/src/test_moving_average.cpp \
$(PROJECT)/src/test_ringbuf.cpp \
$(PROJECT)/src/test_atomic.cpp \
$(PROJECT)/src/test_sharp_memlcd.cpp \
$(PROJECT)/src/test_font8x8.cpp \
$(PROJECT)/src/test_bitzoom.c \
$(PROJECT)/src/test_pulse_density.c \
$(PROJECT)/src/test_pulse_density.cpp \
$(PROJECT)/src/test_bitblit1d.cpp \
$(PROJECT)/src/test_rmw.cpp \
$(PROJECT)/src/test_bitblit2d.cpp \
$(PROJECT)/src/test_elementpack.cpp \
$(PROJECT)/src/test_bitblit2dsmall.cpp

INCLUDES += -I$(PROJECT)/inc

DEFINES += -DMINUNIT_MAX_TESTS=1000

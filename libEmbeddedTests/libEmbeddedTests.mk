# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# project settings
#
# Version: 20200722

# additional library includes
include squantorMinUnit/squantorMinUnit.mk
include libEmbedded/libEmbedded.mk

# project settings
TARGET = PC

# project sources
FILES += $(PROJECT)/src/main.cpp \
$(PROJECT)/src/testArray.cpp \
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
$(PROJECT)/src/test_prompt_mini.c

INCLUDES += -I$(PROJECT)/inc

DEFINES += -DMINUNIT_MAX_TESTS=1000

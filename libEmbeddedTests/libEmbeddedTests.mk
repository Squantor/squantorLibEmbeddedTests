# MIT License

# Copyright (c) 2020 Bart Bilos

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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

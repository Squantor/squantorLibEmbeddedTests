# SPDX-License-Identifier: MIT
# Copyright (c) 2022 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20220715

# current makefile base dir relative to Makefile
BASE_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# include all libraries
include $(BASE_DIR)/libMcuLL/libMcuLL.mak
include $(BASE_DIR)/squantorMinUnit/squantorMinUnit.mak
include $(BASE_DIR)/squantorLibEmbedded/squantorLibEmbedded.mak
include $(BASE_DIR)/squantorLibEmbedded/squantorLibEmbeddedCortexM.mak


# --- nothing user definable below ---

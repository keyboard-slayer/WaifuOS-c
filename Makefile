# Copyright (C) 2022 Keyboard Slayer & contributor
# 
# This file is part of WaifuOS.
# 
# WaifuOS is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# WaifuOS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with WaifuOS.  If not, see <http://www.gnu.org/licenses/>.


MKCWD = mkdir -p $(@D)
BUILD = .build
BINDIR_HOST = .build_host
BOOT = .boot

WARNINGS = 								\
	-Wall								\
	-Wextra								\
	-Werror								\
	-Wpedantic

INCLUDES =								\
	-Isrc/libs/libc/extension/include/	\
	-Isrc/libs/libc/chadlibc/include/	\
	-Isrc/libs/libc/ext/				\
	-Isrc/libs/							\
	-Isrc/

DEFINES =								\
	-DSTB_SPRINTF_NOFLOAT				\
	-DSTB_SPRINTF_IMPLEMENTATION	

DISABLED =								\
	-Wno-variadic-macros				\

CFLAGS = 								\
	$(WARNINGS)							\
	$(INCLUDES)							\
	$(DEFINES)							\
	$(DISABLED)							\
	-std=c89							\
	-O0									\
	-g3									\
	-pedantic


ASFLAGS = 								\
	-Os									\
	-g

LDFLAGS = 								\
	-g									\
	-nostdlib							\
	-static								\

CONF = python meta/config.py

export MENUCONFIG_STYLE?=aquatic

.PHONY: defconfig
defconfig:
	$(CONF) --defconfig
	$(CONF) --genmake .config.mk

.PHONY: menuconfig
menuconfig:
	$(CONF) --menuconfig
	$(CONF) --genmake .config.mk

ifeq (, $(wildcard ./.config))
.PHONY: all
all:
	@echo "Please run 'make defconfig' or 'make menuconfig' first"
else

include .config.mk
include src/apps/.build.mk
include src/libs/libc/.build.mk
include src/libs/abstract/.build.mk
include src/kernel/.build.mk

.PHONY: all
all: $(KERNEL)

endif

.PHONY: clean

clean:
	rm -rf $(BUILD) $(KERNEL) $(BOOT) $(BINDIR_HOST)

boot_skel:
	mkdir -p $(BOOT)/boot $(BOOT)/bin $(BOOT)/EFI/BOOT $(BOOT)/media
	cp $(KERNEL) $(BOOT)/boot
	cp ./meta/aqua.tga $(BOOT)/media

boot: $(KERNEL) boot_skel $(LOADER_FILE)

run: boot
	$(EMU) $(EMUFLAGS)

.SUFFIXES:
.DEFAULT_GOAL: all
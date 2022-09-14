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

include src/apps/*/.build.mk

LIBS_HOST_SRC = 								\
		$(wildcard src/libs/abstract/sdl/*.c)	\
		$(wildcard src/libs/abstract/posix/*.c)	\
		$(wildcard src/libs/ui/*.c)

LIBS_HOST_OBJ = $(patsubst src/%, $(BINDIR_HOST)/%.o, $(LIBS_HOST_SRC))

HOST_CC = gcc
HOST_CFLAGS = $(filter-out -Isrc/libs/libc/chadlibc/include/ -Isrc/libs/libc/ext/, $(CFLAGS))
HOST_CFLAGS += 									\
		-fsanitize=undefined 					\
		-fsanitize=address 						\
		-I/usr/include/SDL2						\
		-D__HOST__

HOST_LDFLAGS = 									\
		-lSDL2									\
		-fsanitize=undefined 					\
		-fsanitize=address

$(BINDIR_HOST)/%.c.o: src/%.c
	@$(MKCWD)
	$(HOST_CC) -c -o $@ $< $(HOST_CFLAGS)

define HOST_TEMPLATE

$(1)_NAME = $$(shell echo $(1) | tr A-Z a-z)

$(1)_HOST_SRC = \
	$$(wildcard src/$$(PKG_$(1)_PATH)/*.c) \
	$$(wildcard src/$$(PKG_$(1)_PATH)/*/*.c) \
	$$(wildcard src/$$(PKG_$(1)_PATH)/*/*/*.c)

$(1)_HOST_OBJ = $$(patsubst src/%,$(BINDIR_HOST)/%.o, $$($(1)_HOST_SRC))
$(1)_HOST_BIN  = $(BINDIR_HOST)/$$($(1)_NAME)

HOST_NAMES+=$$($(1)_NAME)
DEPENDENCIES += $$($(1)_HOST_OBJ:.o=.d)

$$($(1)_NAME): $$($(1)_HOST_BIN)
	@$$($(1)_HOST_BIN)

$$($(1)_HOST_BIN): $$($(1)_HOST_OBJ) $(LIBS_HOST_OBJ)
	@$$(MKCWD)
	$(HOST_CC) -o $$@ $$^ $(HOST_LDFLAGS) $(HOST_CFLAGS)

host-$$($(1)_NAME)-dump:
	@echo "$(1)"
	@echo "$$($(1)_HOST_BIN)"
	@echo "$$($(1)_HOST_OBJ)"
	@echo "$$($(1)_HOST_SRC)"

endef

HOST_PKGS=$(APPS)

list-host:
	@echo $(HOST_NAMES)

$(foreach bin, $(HOST_PKGS), $(eval $(call HOST_TEMPLATE,$(bin))))
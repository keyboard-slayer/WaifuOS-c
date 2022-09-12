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
		$(wildcard src/libs/ui/*.c)

HOST_CC = gcc
HOST_CFLAGS = 									\
		$(CFLAGS) 								\
		-fsanitize=undefined 					\
		-fsanitize=address 						\
		$(sdl2-config --cflags)

HOST_LDFLAGS = 									\
		$(sdl2-config --libs) 					\
		-fsanitize=undefined 					\
		-fsanitize=address

$(BINDIR_HOST)/%.c.o: src/%.c
	@$(MKCWD)
	$(HOST_CC) -c -o $@ $< $(HOST_CFLAGS)


define HOST_TEMPLATE

$(1)_NAME = $$(shell echo $(1) | tr A-Z a-z)

$(1)_HOST_SRC = \
	$$(wildcard src/apps$$(PKG_$(1)_PATH)/*.c) \
	$$(wildcard src/apps$$(PKG_$(1)_PATH)/*/*.c) \
	$$(wildcard src/apps$$(PKG_$(1)_PATH)/*/*/*.c)

$(1)_HOST_OBJ = $$(patsubst src/%,$(BINDIR_HOST)/%.o, $$($(1)_HOST_SRC))
$(1)_HOST_BIN  = $(BINDIR_HOST)/$$($(1)_NAME)

HOST_NAMES+=$$($(1)_NAME)
DEPENDENCIES += $$($(1)_HOST_OBJ:.o=.d)

$$($(1)_NAME): $$($(1)_HOST_BIN)
	@$$(1)_HOST_BIN

$$($(1)_HOST_BIN): $$($(1)_HOST_OBJ) $(LIBS_HOST_BIN)
	@$$(MKCWD)
	$(HOST_CC) -o $$@ $$^ $(HOST_LDFLAGS) $(HOST_CFLAGS)

host-$$($(1)_NAME)-dump:
	@echo "$$($(1)_HOST_BIN)"
	@echo "$$($(1)_HOST_OBJ)"
	@echo "$$($(1)_HOST_SRC)"

endef

HOST_PKGS=$(APPS)

list-host:
	@echo $(HOST_NAMES)

$(foreach bin, $(HOST_PKGS), $(eval $(call HOST_TEMPLATE,$(bin))))
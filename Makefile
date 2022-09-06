
MKCWD = mkdir -p $(@D)
BUILD = .build
BOOT = .boot

WARNINGS = 							\
	-Wall							\
	-Wextra							\
	-Werror							\
	-Wpedantic

INCLUDES =							\
	-Isrc/libc/extension/include/	\
	-Isrc/libc/chadlibc/include/	\
	-Isrc/libc/ext/					\
	-Isrc/

DEFINES =							\
	-DSTB_SPRINTF_NOFLOAT			\
	-DSTB_SPRINTF_IMPLEMENTATION	

DISABLED =							\
	-Wno-variadic-macros			\
	-fno-builtin					\
	-fno-stack-protector			\
	-nostdlib 						\

CFLAGS = 							\
	$(WARNINGS)						\
	$(INCLUDES)						\
	$(DEFINES)						\
	$(DISABLED)						\
	-std=c89						\
	-O0								\
	-g3								\
	-pedantic


ASFLAGS = 							\
	-Os								\
	-g

LDFLAGS = 							\
	-g								\
	-nostdlib						\
	-static							\

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
include src/arch/.build.mk
include src/libc/.build.mk
include src/loader/.build.mk
include src/kernel/.build.mk

.PHONY: all
all: $(KERNEL)

endif

.PHONY: clean

clean:
	rm -rf $(BUILD) $(KERNEL) $(BOOT)

boot_skel:
	mkdir -p $(BOOT)/boot $(BOOT)/bin $(BOOT)/EFI/BOOT $(BOOT)/media
	cp $(KERNEL) $(BOOT)/boot
	cp ./meta/aqua.qoi $(BOOT)/media

boot: $(KERNEL) boot_skel $(LOADER_FILE)

run: boot
	$(EMU) $(EMUFLAGS)

.SUFFIXES:
.DEFAULT_GOAL: all
ifeq ($(CONFIG_ARCH_X86-64), y)
include src/arch/x86_64/.build.mk
else
$(error "No architecture selected")
endif

ifeq ($(CONFIG_LOADER_LIMINE), y)
include src/libs/abstract/limine/.build.mk
else
$(error "No loader selected")
endif

KERNEL_SRC += $(wildcard src/libs/abstract/*.c)
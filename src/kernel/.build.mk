KERNEL = $(BUILD)/kernel.elf
KERNEL_BUILD = $(BUILD)/kernel

KERNEL_CFLAGS +=                                        \
        $(CFLAGS)                                       \
        -fno-zero-initialized-in-bss    		\
        -mno-sse                                        \
        -mno-sse2                                       \
        -mcmodel=kernel                                 \
        -D__kernel__					\

KERNEL_LDFLAGS +=                                       \
        $(LDFLAGS)                                      \
        -no-pie                                         \
        -m elf_x86_64

KERNEL_SRC +=                                           \
        $(wildcard src/kernel/*.c)              	\
        $(LIBC_SRC)

KERNEL_OBJ := $(patsubst %, $(KERNEL_BUILD)/%.o, $(KERNEL_SRC))
DEPENDENCIES += $(KERNEL_OBJ:.o=.d)

$(KERNEL_BUILD)/%.c.o: %.c
		@$(MKCWD)
		$(CROSS_CC) -c -o $@ $< $(KERNEL_CFLAGS)

$(KERNEL_BUILD)/%.s.o: %.s
		@$(MKCWD)
		$(CROSS_AS) -o $@ $< $(ASFLAGS)

$(KERNEL): $(KERNEL_OBJ)
		@$(MKCWD)
		$(CROSS_LD) $(KERNEL_LDFLAGS) -o $@ $^

CROSS_CC = gcc
CROSS_AS = as
CROSS_LD = ld

EMU = qemu-system-x86_64
EMUFLAGS = 													\
	-no-reboot												\
	-serial mon:stdio										\
	-smp $(CONFIG_CPU_CORE)									\
	-m $(CONFIG_MEMORY)M									\
	-M q35													\

ifeq ($(CONFIG_ENABLE_KVM), y)
EMUFLAGS += -enable-kvm -cpu host
endif

ifeq ($(CONFIG_DUMP_INTERRUPT), y)
EMUFLAGS += -d int
endif

ifeq ($(CONFIG_LOADER_EFI), y)
EMUFLAGS += -drive file=fat:rw:$(BOOT),media=disk,format=raw		\
			-bios $(CONFIG_EFI_BIOS_PATH)
else
EMUFLAGS += -drive format=raw,file=kernel.iso
endif

ifeq ($(CONFIG_NO_POWEROFF), y)
EMUFLAGS += -no-shutdown
endif

CONFIG_COM_PORT_1 = 0x3f8
CONFIG_COM_PORT_2 = 0x2f8
CONFIG_COM_PORT_3 = 0x3e8
CONFIG_COM_PORT_4 = 0x2e8

IS_BAUD_VALID = $(shell echo $(( $(CONFIG_BAUD_RATE) % 115200 )))
ifeq ($(IS_BAUD_VALID), 0)
$(error "$(CONFIG_BAUD_RATE) bauds is not a valid baud rate")
endif

KERNEL_CFLAGS = -D__DEBUG_SERIAL__=${CONFIG_COM_PORT_${CONFIG_SERIAL_PORT}}	 	\
				-D__DEBUG_SERIAL_BAUDS__=$(CONFIG_BAUD_RATE)					\
				-ffreestanding													\
		  		-m64										 					\
				-march=x86-64        											\
    			-mabi=sysv           											\
		  		-mno-sse														\
		  		-mno-sse2														\
		  		-fno-pic														\
		  		-fno-pie														\
				-fno-lto														\
				-Wvla 															\
    			-Wshadow 														\
		  		-mno-red-zone													\
				-D__x86_64__													\

KERNEL_LDFLAGS = -z max-page-size=0x1000

KERNEL_SRC += $(wildcard src/arch/x86_64/*.c) $(wildcard src/arch/x86_64/*.s) $(wildcard src/arch/cross-x86/*.c)


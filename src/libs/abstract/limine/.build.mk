ifeq ($(CONFIG_LOADER_EFI), y)
	LOADER_FILE = $(BOOT)/EFI/BOOT/BOOTX64.EFI
else 
	LOADER_FILE = kernel.iso
endif

KERNEL_LDFLAGS += -Tsrc/libs/abstract/limine/linker.ld
KERNEL_SRC += $(wildcard src/libs/abstract/limine/*.c)
VER = 4.0

$(BOOT)/boot/limine.cfg:
	cp ./src/libs/abstract/limine/limine.cfg $(BOOT)/boot/

$(BOOT)/EFI/BOOT/BOOTX64.EFI: $(BOOT)/boot/limine.cfg
	wget https://github.com/limine-bootloader/limine/raw/v$(VER)-binary/BOOTX64.EFI -O $(BOOT)/EFI/BOOT/BOOTX64.EFI

./limine-deploy.c:
	wget https://github.com/limine-bootloader/limine/raw/v$(VER)-binary/limine-deploy.c -O limine-deploy.c

./limine-hhd.h:
	wget https://github.com/limine-bootloader/limine/raw/v$(VER)-binary/limine-hdd.h -O limine-hdd.h

./limine-deploy: ./limine-deploy.c ./limine-hhd.h
	cc -g -o2 -pipe -Wall -Wextra -std=c99 -D__USE_MINGW_ANSI_STDIO limine-deploy.c -o ./limine-deploy
	rm limine-deploy.c limine-hdd.h

$(BOOT)/boot/limine-cd.bin:
	wget https://github.com/limine-bootloader/limine/raw/v$(VER)-binary/limine-cd.bin -O $(BOOT)/boot/limine-cd.bin

$(BOOT)/boot/limine-cd-efi.bin:
	wget https://github.com/limine-bootloader/limine/raw/v$(VER)-binary/limine-cd-efi.bin -O $(BOOT)/boot/limine-cd-efi.bin

$(BOOT)/boot/limine.sys:
	wget https://github.com/limine-bootloader/limine/raw/v$(VER)-binary/limine.sys -O $(BOOT)/boot/limine.sys

kernel.iso: $(BOOT)/boot/limine.cfg ./limine-deploy $(BOOT)/boot/limine.sys $(BOOT)/boot/limine-cd.bin $(BOOT)/boot/limine-cd-efi.bin
	xorriso -as mkisofs -b /boot/limine-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot /boot/limine-cd-efi.bin -efi-boot-part --efi-boot-image --protective-msdos-label \
		$(BOOT) -o kernel.iso
	
	./limine-deploy kernel.iso
	rm limine-deploy
# ToyOS

# Tools
ASM		= nasm			# Assembler
CC		= i686-elf-gcc	# Cross-compiler
LD		= i686-elf-ld	# GNU Linker

# Compiler Flags
CFLAGS	= -ffreestanding -02 -Wall -Wextra -fno-exceptions

# Output
OS_IMAGE = os.img

all: $(OS_IMAGE)

# Bootlader Assembly
boot/boot.bin: boot/boot-32.asm
	$(ASM)) -f bin $< -o $@

# Compile the kernel
kernel/kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link the kernel file into a flat binary
kernel/kernel.bin: kernel.kernel.o
	$(LD) -T linker.ld -o $@ --oformat binary $

# Combine bootloader and kernel
$(OS_IMAGE): boot/boot.bin kernel/kernel.bin
	cat boot/boot.bin kernel/kernel.bin > $(OS_IMAGE)

# QEMU
run: $(OS_IMAGE)
	qemu-system-i386 -drive format=raw,file=$(OS_IMAGE)

# Clean artifacts
clean:
	rm -f boot/boot.bin kernel/kernel.o kernel/kernel.bin $(OS_IMAGE)
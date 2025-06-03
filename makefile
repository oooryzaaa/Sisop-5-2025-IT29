# Path
SRC = src
BIN = bin
INC = include

# Tools
CC = gcc
LD = ld
AS = nasm
OBJCOPY = objcopy

# Build steps
prepare:
	mkdir -p $(BIN)
	dd if=/dev/zero of=$(BIN)/floppy.img bs=512 count=2880

bootloader:
	$(AS) $(SRC)/bootloader.asm -f bin -o $(BIN)/bootloader.bin

stdlib:
	$(CC) -m32 -ffreestanding -I$(INC) -c $(SRC)/std_lib.c -o $(BIN)/std_lib.o

shell:
	$(CC) -m32 -ffreestanding -I$(INC) -c $(SRC)/shell.c -o $(BIN)/shell.o

kernel:
	$(CC) -m32 -ffreestanding -I$(INC) -c $(SRC)/kernel.c -o $(BIN)/kernel.o
	$(AS) $(SRC)/kernel.asm -f elf -o $(BIN)/kernel_asm.o

link:
	$(LD) -m elf_i386 -Ttext 0x1000 -o $(BIN)/kernel.elf $(BIN)/kernel.o $(BIN)/kernel_asm.o $(BIN)/shell.o $(BIN)/std_lib.o
	$(OBJCOPY) -O binary $(BIN)/kernel.elf $(BIN)/kernel.bin
	cat $(BIN)/bootloader.bin $(BIN)/kernel.bin > $(BIN)/floppy.img

build: prepare bootloader stdlib shell kernel link

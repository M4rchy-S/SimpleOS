CC=/home/ubuntu/i386elfgcc/bin/i386-elf-gcc
ASM=/home/ubuntu/i386elfgcc/bin/i386-elf-as
NASM=nasm

SRC_DIR=src
BUILD_DIR=build

# SRCS_C := src/kernel/kernel.c
# SRCS_S := src/boot.s

OBJS_C := $(BUILD_DIR)/kernel.o
OBJS_S := $(BUILD_DIR)/boot.o $(BUILD_DIR)/load_gdt.o $(BUILD_DIR)/idt_isr.o 

OBJS = ${OBJS_C} ${OBJS_S}

# CFLAGS?= -O2
CFLAGS?= -g -m32 
CFLAGS:= $(CFLAGS) -std=gnu99 -ffreestanding -O2 -Wall -Wextra 
LINK_FLAGS?= -ffreestanding $(OBJS) -O2 -nostdlib -lgcc
NASM_FLAGS ?=  -f elf32

.PHONY: all clean always

OS_NAME=myos.bin

floppy_image: $(BUILD_DIR)/$(OS_NAME)
$(BUILD_DIR)/$(OS_NAME): kernel assems
	$(CC) -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/$(OS_NAME) $(LINK_FLAGS) 

assems: $(BUILD_DIR)/boot.o
$(BUILD_DIR)/boot.o: always
	$(ASM) src/boot.s -o $(BUILD_DIR)/boot.o
	$(NASM) src/kernel/tables/asm/load_gdt.s -o $(BUILD_DIR)/load_gdt.o $(NASM_FLAGS)
	$(NASM) src/kernel/tables/asm/idt_isr.s -o $(BUILD_DIR)/idt_isr.o $(NASM_FLAGS)


kernel: $(BUILD_DIR)/kernel.o
$(BUILD_DIR)/kernel.o: always
	$(CC) $(CFLAGS) -c src/kernel/kernel.c -o $(BUILD_DIR)/kernel.o


always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*







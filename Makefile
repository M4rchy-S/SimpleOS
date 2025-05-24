CC=/home/ubuntu/i386elfgcc/bin/i386-elf-gcc
ASM=/home/ubuntu/i386elfgcc/bin/i386-elf-as

SRC_DIR=src
BUILD_DIR=build

SRCS_C := src/kernel/kernel.c
SRCS_S := src/boot.s

OBJS_C := $(BUILD_DIR)/kernel.o
OBJS_S := $(BUILD_DIR)/boot.o 

OBJS = ${OBJS_C} ${OBJS_S}

# CFLAGS?= -O2
CFLAGS?= -g
CFLAGS:= $(CFLAGS) -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LINK_FLAGS?= -ffreestanding $(OBJS) -O2 -nostdlib -lgcc 

.PHONY: all clean always

OS_NAME=myos.bin

floppy_image: $(BUILD_DIR)/$(OS_NAME)
$(BUILD_DIR)/$(OS_NAME): bootloader kernel
	$(CC) -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/$(OS_NAME) $(LINK_FLAGS) 

bootloader: $(OBJS_S)
$(OBJS_S): always
	$(ASM) src/boot.s -o $(BUILD_DIR)/boot.o

kernel: $(OBJS_C)
$(OBJS_C): always
	$(CC) $(CFLAGS) -c src/kernel/kernel.c -o $(BUILD_DIR)/kernel.o


# kernel: $(OBJS_A) $(OBJS_C)
# $(BUILD_DIR)/%.o: always $(SRCS_A) $(SRCS_C)
# 	$(CC) $(CFLAGS) -c $(SRCS_C) -o $(BUILD_DIR)/kernel.o
# 	$(ASM) $(SRCS_A) -o $(BUILD_DIR)/assembs.o



always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*







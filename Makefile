CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

PROJECT_DIR = $(HOME)/Data/Uni/CSCI490/Project/plant-monitor-sam3x8e
BUILD_DIR = $(PROJECT_DIR)/build

CPPFLAGS = \
	   -I./sam3xa/include \
	   -I./hal/include \
	   -I./drivers/include \
	   -I./include \
	   -D__SAM3X8E__

CFLAGS = \
	 -mcpu=cortex-m3 \
	 -mthumb \
	 -O0 \
	 -Wall \
	 -Wextra \
	 -Wpedantic \
	 -g

LDFLAGS = \
	  -mcpu=cortex-m3 \
	  -mthumb \
	  -T./sam3xa/source/gcc_atmel/sam3x8e_flash.ld \
	  -L./sam3xa/source/gcc_atmel \
	  -nostartfiles

OBJS = \
       $(BUILD_DIR)/main.o \
       $(BUILD_DIR)/display.o \
       $(BUILD_DIR)/pio.o \
       $(BUILD_DIR)/spi.o \
       $(BUILD_DIR)/twi.o \
       $(BUILD_DIR)/time.o \
       $(BUILD_DIR)/st7789.o \
       $(BUILD_DIR)/bme280.o \
       $(BUILD_DIR)/startup_sam3xa.o

.PHONY: all elf clean

all: $(BUILD_DIR)/firmware.bin

elf: $(BUILD_DIR)/firmware.elf

clean:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/main.o: src/main.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/display.o: src/display.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/pio.o: hal/src/pio.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/spi.o: hal/src/spi.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/twi.o: hal/src/twi.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/time.o: hal/src/time.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/st7789.o: drivers/src/st7789.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/bme280.o: drivers/src/bme280.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/startup_sam3xa.o: sam3xa/source/gcc_atmel/startup_sam3xa.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/firmware.elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/firmware.bin: $(BUILD_DIR)/firmware.elf
	$(OBJCOPY) -O binary $< $@


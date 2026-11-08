CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

PROJECT_DIR = $(CURDIR)
BUILD_DIR = $(PROJECT_DIR)/build

CPPFLAGS = \
	   -I./sam3xa/include \
	   -I./hal/include \
	   -I./drivers/include \
	   -I./kernel/include \
	   -I./kernel/portable/GCC/ARM_CM3 \
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

APP_SRCS = \
       src/main.c \
       src/display.c \
       src/sensors.c \
       src/convert.c

DRIVER_SRCS = \
	drivers/src/st7789.c \
	drivers/src/bme280.c

HAL_SRCS = \
	hal/src/pio.c \
	hal/src/spi.c \
	hal/src/twi.c \
	hal/src/time.c

FREERTOS_SRCS = \
	kernel/tasks.c \
	kernel/queue.c \
	kernel/list.c \
	kernel/timers.c \
	kernel/stream_buffer.c \
	kernel/croutine.c \
	kernel/event_groups.c \
	kernel/portable/GCC/ARM_CM3/port.c \
	kernel/portable/MemMang/heap_4.c

STARTUP_SRCS = \
	sam3xa/source/gcc_atmel/startup_sam3xa.c

APP_OBJS      = $(patsubst %.c,$(BUILD_DIR)/%.o,$(APP_SRCS))
DRIVER_OBJS   = $(patsubst %.c,$(BUILD_DIR)/%.o,$(DRIVER_SRCS))
HAL_OBJS      = $(patsubst %.c,$(BUILD_DIR)/%.o,$(HAL_SRCS))
FREERTOS_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(FREERTOS_SRCS))
STARTUP_OBJS  = $(patsubst %.c,$(BUILD_DIR)/%.o,$(STARTUP_SRCS))

OBJS = \
	$(APP_OBJS) \
	$(DRIVER_OBJS) \
	$(HAL_OBJS) \
	$(FREERTOS_OBJS) \
	$(STARTUP_OBJS)

.PHONY: all elf clean

all: $(BUILD_DIR)/firmware.bin

elf: $(BUILD_DIR)/firmware.elf

clean:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/firmware.elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/firmware.bin: $(BUILD_DIR)/firmware.elf
	$(OBJCOPY) -O binary $< $@

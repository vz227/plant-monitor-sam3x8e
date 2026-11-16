CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
DOXYGEN = doxygen

PROJECT_DIR = $(CURDIR)
BUILD_DIR   = $(PROJECT_DIR)/build
DOCS_DIR    = $(PROJECT_DIR)/docs

CPPFLAGS = \
    -I./lib/sam3xa/include \
    -I./lib/freertos/include \
    -I./lib/freertos/portable/GCC/ARM_CM3 \
    -I./include \
    -I./include/freertos \
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
    -T./lib/sam3xa/source/gcc_atmel/sam3x8e_flash.ld \
    -L./lib/sam3xa/source/gcc_atmel \
    -nostartfiles

APP_SRCS = \
    src/application/main.c \
    src/application/display.c \
    src/application/sensors.c \
    src/application/format.c \
    src/application/tasks.c

DRIVER_SRCS = \
    src/drivers/st7789.c \
    src/drivers/bme280.c \
    src/drivers/ek1940.c

HAL_SRCS = \
    src/hal/pio.c \
    src/hal/spi.c \
    src/hal/twi.c \
    src/hal/adc.c \
    src/hal/tc.c

FREERTOS_SRCS = \
    lib/freertos/tasks.c \
    lib/freertos/queue.c \
    lib/freertos/list.c \
    lib/freertos/timers.c \
    lib/freertos/stream_buffer.c \
    lib/freertos/croutine.c \
    lib/freertos/event_groups.c \
    lib/freertos/portable/GCC/ARM_CM3/port.c \
    lib/freertos/portable/MemMang/heap_4.c

STARTUP_SRCS = \
    lib/sam3xa/source/gcc_atmel/startup_sam3xa.c

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

.PHONY: all elf docs clean

all: $(BUILD_DIR)/firmware.bin docs

elf: $(BUILD_DIR)/firmware.elf

clean:
	rm -rf $(BUILD_DIR) $(DOCS_DIR)

docs:
	$(DOXYGEN) Doxyfile

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/firmware.elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/firmware.bin: $(BUILD_DIR)/firmware.elf
	$(OBJCOPY) -O binary $< $@

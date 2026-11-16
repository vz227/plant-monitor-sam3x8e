# Plant Monitor System for ATSAM3X8E

## Overview

Embedded plant monitoring system for the ATSAM3X8E ARM Cortex-M3 microcontroller. Currently monitors relative humidity, atmospheric pressure, ambient temperature, and soil moisture.

## Features

- Relative humidity, atmospheric pressure, and temperature measurements using BME280
- Soil moisture measurement using EK1940
- Real-time measurement retrieval & display
- Concurrent measurement tasks using FreeRTOS kernel
- Custom peripheral drivers and hardware abstraction layer (HAL)
  
## Requirements

### Hardware

- ATSAM3X8E Microcontroller
- Waveshare 2-inch LCD Module w/ ST7789 Controller
- BME280 Environment Sensor
- EK1940 Capacitive Soil Moisture Sensor

### Software

- ARM GNU Toolchain
- GNU Make
- BOSSA

## Building \& Flashing

### Linux

#### Building

The firmware can be compiled using the ARM GNU Toolchain and GNU Make.

Invoke from within repository root:

```sh
make all
```
The resulting binary and ELF executable can be found in `build/`. The ELF executable can be used for debugging with GDB.

#### Flashing

Connect the SAM3X8E board through its programming port and identify the serial device under `/dev`, typically under the pattern `/dev/ttyACM*`.

Finally, flash the firmware using BOSSA:

**Warning: This operation overwrites existing firmware.**

```sh
bossac -p <path to programming port> -e -w build/firmware.bin --boot=1
```

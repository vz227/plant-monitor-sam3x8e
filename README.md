# Plant Monitor System w/ SAM3X8E

A plant monitor system that runs on the SAM3X8E microcontroller displaying ambient temperature, light, humidity, and soil moisture.

## Dependencies

The following hardware and software are required for this software to run:

### Hardware

- SAM3X8E Microcontroller
- Waveshare 2-inch LCD Module w/ ST7789 Controller
- BME280 Environment Sensor
- SEN0193 Capacitive Soil Moisture Sensor
- GY-302 BH1750FVI Ambient Light Sensor

### Software

- ARM GNU Toolchain
- GNU Make
- BOSSA Flash Programming Utility

## Building \& Installing

### Linux

Compilation has been tested using the ARM GNU Toolchain. To build, simply run from within the repo directory:

```sh
make all
```

Once compiled, the firmware can be uploaded by invoking BOSSA:

```sh
bossac -p <Path to programming port> -e -w build/firmware.bin --boot=1
```

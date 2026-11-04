/** @file sensors.c
 *  @brief Wrapper for sensor drivers to retrieve human-readable measurements.
 *
 *  Contains function implementations from sensors.h
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date October 25th, 2026
 */

#include "sensors.h"

void sensors_init()
{
    bme280_init();
}

int32_t read_temp()
{
    uint8_t temp_buffer[TEMP_LEN];
    bme280_read_temp(temp_buffer);

    int32_t adc_temp =
        ((int32_t)temp_buffer[0] << 12) |
        ((int32_t)temp_buffer[1] << 4)  |
        ((int32_t)temp_buffer[2] >> 4);

    int32_t temp = bme280_compensate_temp(adc_temp);
    return temp;
}

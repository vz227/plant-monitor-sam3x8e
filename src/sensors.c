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

uint32_t read_humidity()
{
    uint8_t hum_buffer[HUMIDITY_LEN];
    bme280_read_humidity(hum_buffer);

    int32_t adc_humidity =
        ((int32_t)hum_buffer[0] << 8) |
        (int32_t)hum_buffer[1];

    uint32_t humidity = bme280_compensate_humidity(adc_humidity);
    return humidity;
}

uint32_t read_pressure()
{
    uint8_t press_buffer[PRESSURE_LEN];
    bme280_read_pressure(press_buffer);

    int32_t adc_pressure =
    ((int32_t)press_buffer[0] << 12) |
    ((int32_t)press_buffer[1] << 4)  |
    ((int32_t)press_buffer[2] >> 4);

    uint32_t pressure = bme280_compensate_pressure(adc_pressure);
    return pressure;
}

int32_t read_temperature()
{
    uint8_t temp_buffer[TEMPERATURE_LEN];
    bme280_read_temp(temp_buffer);

    int32_t adc_temp =
        ((int32_t)temp_buffer[0] << 12) |
        ((int32_t)temp_buffer[1] << 4)  |
        ((int32_t)temp_buffer[2] >> 4);

    int32_t temp = bme280_compensate_temp(adc_temp);
    return temp;
}

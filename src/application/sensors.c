/** @file sensors.c
 *  @brief High-level functions for retrieving sensor data.
 *
 * Contains implementations of wrapper functions for sensor
 * drivers to retrieve sensor measurements.
 *
 * @author Vladimir Zhelev
 */

#include "application/sensors.h"

measurements_t sensor_data;

void sensors_init(void)
{
    bme280_init();
    ek1940_init();
}

void read_humidity(void)
{
    uint8_t hum_buffer[HUMIDITY_LEN];
    bme280_read_humidity(hum_buffer);

    int32_t adc_humidity =
        ((int32_t)hum_buffer[0] << 8) |
        (int32_t)hum_buffer[1];

    sensor_data.humidity = bme280_compensate_humidity(adc_humidity);
}

void read_pressure(void)
{
    uint8_t press_buffer[PRESSURE_LEN];
    bme280_read_pressure(press_buffer);

    int32_t adc_pressure =
    ((int32_t)press_buffer[0] << 12) |
    ((int32_t)press_buffer[1] << 4)  |
    ((int32_t)press_buffer[2] >> 4);

    sensor_data.pressure = bme280_compensate_pressure(adc_pressure);
}

void read_temperature(void)
{
    uint8_t temp_buffer[TEMPERATURE_LEN];
    bme280_read_temp(temp_buffer);

    int32_t adc_temp =
        ((int32_t)temp_buffer[0] << 12) |
        ((int32_t)temp_buffer[1] << 4)  |
        ((int32_t)temp_buffer[2] >> 4);

    sensor_data.temperature = bme280_compensate_temp(adc_temp);
}

void read_moisture(void)
{
    uint16_t adc_moisture = 0;
    ek1940_read_moisture(&adc_moisture);

    sensor_data.moisture = ek1940_compensate_moisture(adc_moisture);
}

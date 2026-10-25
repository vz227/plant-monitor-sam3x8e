/** @file bme280.c
 *  @brief Driver for the BME280 humidity & pressure sensor.
 *
 *  Contains function implementations from bme280.h
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date October 8th, 2026
 */

#include "bme280.h"

void bme280_init()
{
    /* Initialize TWI0 */
    twi_init();

    twi_msg_cfg_t init_msg = {
        .dadr = BME280_ADDR,
        .iadr = 0,
        .iadr_size = TWI_ADDR_0BYTE
    };

    uint8_t cfg[2] = { CTRLMEAS_ADDR, 0x27 };

    twi_msg_configure(&init_msg);
    twi_write(cfg, sizeof(cfg));
}

void bme280_read_humidity(uint8_t* buffer)
{
    return;
}

void bme280_read_pressure(uint8_t* buffer)
{
    return;
}

void bme280_read_temp(uint8_t* buffer)
{
    /* Configure TWI message */
    twi_msg_cfg_t read_temp_msg = {
        .dadr = BME280_ADDR,
        .iadr = TEMP_ADDR,
        .iadr_size = TWI_ADDR_1BYTE
    };

    twi_msg_configure(&read_temp_msg);
    twi_read(buffer, TEMP_LEN);
}

int32_t bme280_compensate_humidity(uint8_t* adc_humidity)
{
    return;
}

int32_t bme280_compensate_pressure(uint8_t* adc_pressure)
{
    return;
}

int32_t bme280_compensate_temp(int32_t adc_temp)
{
    int32_t var1, var2, temp;
    var1  = ((((adc_temp >> 3) – ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    var2  = (((((adc_temp >> 4) – ((uint32_t)dig_T1)) * ((adc_temp >> 4) – ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
    int32_t temp_fine = var1 + var2;
    int32_t temp_centi_c  = (temp_fine * 5 + 128) >> 8;
    return temp_centi_c;
}

void bme280_read_status(uint8_t* buffer)
{
    twi_msg_cfg_t read_status_msg = {
        .dadr = BME280_ADDR,
        .iadr = STATUS_ADDR,
        .iadr_size = TWI_ADDR_1BYTE
    };

    twi_msg_configure(&read_status_msg);
    twi_read(buffer, STATUS_LEN);
}

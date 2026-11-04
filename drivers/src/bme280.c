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

static bme280_t bme280;

static void bme280_read_reg(twi_cfg_t* cfg, uint8_t* buffer, uint8_t len)
{
    twi_configure(cfg);
    twi_read(buffer, len);
}

void bme280_init()
{
    twi_init();
    twi_cfg_t init_cfg = {
        .dadr = BME280_ADDR,
        .iadr = 0,
        .iadr_size = TWI_ADDR_0BYTE
    };
    uint8_t ctrlmeas_cfg[2] = { CTRLMEAS_ADDR, 0x27 };
    twi_configure(&init_cfg);
    twi_write(ctrlmeas_cfg, sizeof(ctrlmeas_cfg));

    uint8_t calib_a[CALIBA_LEN];
    uint8_t calib_b[CALIBB_LEN];

    bme280_read_calib_a(calib_a);
    bme280_read_calib_b(calib_b);

    bme280.dig_T1 = (uint16_t)((calib_a[1] << 8) | calib_a[0]);
    bme280.dig_T2 = (int16_t)((calib_a[3] << 8) | calib_a[2]);
    bme280.dig_T3 = (int16_t)((calib_a[5] << 8) | calib_a[4]);
}

void bme280_read_temp(uint8_t* buffer)
{
    twi_cfg_t read_temp_cfg = {
        .dadr = BME280_ADDR,
        .iadr = TEMP_ADDR,
        .iadr_size = TWI_ADDR_1BYTE
    };
    bme280_read_reg(&read_temp_cfg, buffer, TEMP_LEN);
}

void bme280_read_status(uint8_t* buffer)
{
    twi_cfg_t read_status_cfg = {
        .dadr = BME280_ADDR,
        .iadr = STATUS_ADDR,
        .iadr_size = TWI_ADDR_1BYTE
    };
    bme280_read_reg(&read_status_cfg, buffer, STATUS_LEN);
}

void bme280_read_calib_a(uint8_t* buffer)
{
    twi_cfg_t read_caliba_cfg = {
        .dadr = BME280_ADDR,
        .iadr = CALIBA_ADDR,
        .iadr_size = TWI_ADDR_1BYTE
    };
    bme280_read_reg(&read_caliba_cfg, buffer, CALIBA_LEN);
}

void bme280_read_calib_b(uint8_t* buffer)
{
    twi_cfg_t read_calibb_cfg = {
        .dadr = BME280_ADDR,
        .iadr = CALIBB_ADDR,
        .iadr_size = TWI_ADDR_1BYTE
    };
    bme280_read_reg(&read_calibb_cfg, buffer, CALIBB_LEN);
}

int32_t bme280_compensate_humidity(uint8_t* adc_humidity)
{
    return 0;
}

int32_t bme280_compensate_pressure(uint8_t* adc_pressure)
{
    return 0;
}

int32_t bme280_compensate_temp(int32_t adc_temp)
{
    int32_t var1, var2, temp;
    var1  = ((((adc_temp >> 3) - ((int32_t)bme280.dig_T1 << 1))) * ((int32_t)bme280.dig_T2)) >> 11;
    var2  = (((((adc_temp >> 4) - ((int32_t)bme280.dig_T1)) * ((adc_temp >> 4) - ((int32_t)bme280.dig_T1))) >> 12) * ((int32_t)bme280.dig_T3)) >> 14;
    int32_t temp_fine = var1 + var2;
    temp = (temp_fine * 5 + 128) >> 8;
    return temp;
}


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
    bme280.dig_P1 = (uint16_t)((calib_a[7] << 8) | calib_a[6]);
    bme280.dig_P2 = (int16_t)((calib_a[9] << 8) | calib_a[8]);
    bme280.dig_P3 = (int16_t)((calib_a[11] << 8) | calib_a[10]);
    bme280.dig_P4 = (int16_t)((calib_a[13] << 8) | calib_a[12]);
    bme280.dig_P5 = (int16_t)((calib_a[15] << 8) | calib_a[14]);
    bme280.dig_P6 = (int16_t)((calib_a[17] << 8) | calib_a[16]);
    bme280.dig_P7 = (int16_t)((calib_a[19] << 8) | calib_a[18]);
    bme280.dig_P8 = (int16_t)((calib_a[21] << 8) | calib_a[20]);
    bme280.dig_P9 = (int16_t)((calib_a[23] << 8) | calib_a[22]);
    bme280.dig_H1 = calib_a[25];
    bme280.dig_H2 = (int16_t)((calib_b[1] << 8) | calib_b[0]);
    bme280.dig_H3 = calib_b[2];
    bme280.dig_H4 = (int16_t)((calib_b[3] << 4) | (calib_b[4] & 0x0F));
    bme280.dig_H5 = (int16_t)((calib_b[5] << 4) | (calib_b[4] >> 4));
    bme280.dig_H6 = (int8_t)calib_b[6];
}

void bme280_read_humidity(uint8_t* buffer)
{
    twi_cfg_t read_humidity_cfg = {
        .dadr = BME280_ADDR,
        .iadr = HUM_ADDR,
        .iadr_size = TWI_ADDR_1BYTE
    };
    bme280_read_reg(&read_humidity_cfg, buffer, HUMIDITY_LEN);
}

void bme280_read_pressure(uint8_t* buffer)
{
    twi_cfg_t read_pressure_cfg = {
        .dadr = BME280_ADDR,
        .iadr = PRESS_ADDR,
        .iadr_size = TWI_ADDR_1BYTE
    };
    bme280_read_reg(&read_pressure_cfg, buffer, PRESSURE_LEN);
}

void bme280_read_temp(uint8_t* buffer)
{
    twi_cfg_t read_temp_cfg = {
        .dadr = BME280_ADDR,
        .iadr = TEMP_ADDR,
        .iadr_size = TWI_ADDR_1BYTE
    };
    bme280_read_reg(&read_temp_cfg, buffer, TEMPERATURE_LEN);
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

uint32_t bme280_compensate_humidity(int32_t adc_humidity)
{
    int32_t v_x1_u32r;
    v_x1_u32r = (bme280.t_fine - ((int32_t)76800));
    v_x1_u32r = (((((adc_humidity << 14) - (((int32_t)bme280.dig_H4) << 20) - (((int32_t)bme280.dig_H5) *
    v_x1_u32r)) + ((int32_t)16384)) >> 15) * (((((((v_x1_u32r *
    ((int32_t)bme280.dig_H6)) >> 10) * (((v_x1_u32r * ((int32_t)bme280.dig_H3)) >> 11) +
    ((int32_t)32768))) >> 10) + ((int32_t)2097152)) * ((int32_t)bme280.dig_H2) +
    8192) >> 14));
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
    ((int32_t)bme280.dig_H1)) >> 4));
    v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
    return (uint32_t)(v_x1_u32r>>12);
}

uint32_t bme280_compensate_pressure(int32_t adc_pressure)
{
    int64_t var1, var2, p;
    var1 = ((int64_t)bme280.t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)bme280.dig_P6;
    var2 = var2 + ((var1*(int64_t)bme280.dig_P5)<<17);
    var2 = var2 + (((int64_t)bme280.dig_P4)<<35);
    var1 = ((var1 * var1 * (int64_t)bme280.dig_P3)>>8) + ((var1 * (int64_t)bme280.dig_P2)<<12);
    var1 = (((((int64_t)1)<<47)+var1))*((int64_t)bme280.dig_P1)>>33;
    if (var1 == 0)
    {
        return 0; // avoid exception caused by division by zero
    }
    p = 1048576-adc_pressure;
    p = (((p<<31)-var2)*3125)/var1;
    var1 = (((int64_t)bme280.dig_P9) * (p>>13) * (p>>13)) >> 25;
    var2 = (((int64_t)bme280.dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)bme280.dig_P7)<<4);
    return (uint32_t)p;
}

int32_t bme280_compensate_temp(int32_t adc_temp)
{
    int32_t var1, var2;
    var1  = ((((adc_temp >> 3) - ((int32_t)bme280.dig_T1 << 1))) * ((int32_t)bme280.dig_T2)) >> 11;
    var2  = (((((adc_temp >> 4) - ((int32_t)bme280.dig_T1)) * ((adc_temp >> 4) - ((int32_t)bme280.dig_T1))) >> 12) * ((int32_t)bme280.dig_T3)) >> 14;
    bme280.t_fine = var1 + var2;
    return (bme280.t_fine * 5 + 128) >> 8;
}


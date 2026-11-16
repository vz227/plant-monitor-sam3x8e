/** @file bme280.c
 *  @brief Interface for BME280 driver.
 *
 * Contains implementations of functions for initializing
 * the BME280, reading, and compensating humidity, pressure,
 * and temperature measurements.
 *
 * @author Vladimir Zhelev
 */

#include "drivers/bme280.h"

static bme280_calib_t bme280_calib;

/**
 * @brief Reads a BME280 register
 *
 * Configures the TWI peripheral accordingly, and reads from the
 * specified internal address into buffer.
 *
 * @param cfg TWI configuration parameters.
 * @param buffer Buffer to store reading.
 * @param len Number of bytes to read into buffer.
 */
static void bme280_read_reg(twi_cfg_t* cfg, uint8_t* buffer, size_t len)
{
    twi_configure(cfg);
    twi_read(buffer, len);
}

/**
 * @brief Reads & stores first set of calibration coefficients
 *
 * Reads first set of calibration coefficients and stores them
 * in global bme280_calib_t variable.
 */
static void bme280_read_calib_a(void)
{
    twi_cfg_t read_caliba_cfg = {
        .dadr = BME280_ADDR,
        .iadr = CALIBA_ADDR,
        .iadr_size = TWI_ADDR_1BYTE
    };
    uint8_t calib_a[CALIBA_LEN];
    bme280_read_reg(&read_caliba_cfg, calib_a, CALIBA_LEN);

    bme280_calib.dig_T1 = (uint16_t)((calib_a[1] << 8) | calib_a[0]);
    bme280_calib.dig_T2 = (int16_t)((calib_a[3]  << 8) | calib_a[2]);
    bme280_calib.dig_T3 = (int16_t)((calib_a[5]  << 8) | calib_a[4]);
    bme280_calib.dig_P1 = (uint16_t)((calib_a[7] << 8) | calib_a[6]);
    bme280_calib.dig_P2 = (int16_t)((calib_a[9]  << 8) | calib_a[8]);
    bme280_calib.dig_P3 = (int16_t)((calib_a[11] << 8) | calib_a[10]);
    bme280_calib.dig_P4 = (int16_t)((calib_a[13] << 8) | calib_a[12]);
    bme280_calib.dig_P5 = (int16_t)((calib_a[15] << 8) | calib_a[14]);
    bme280_calib.dig_P6 = (int16_t)((calib_a[17] << 8) | calib_a[16]);
    bme280_calib.dig_P7 = (int16_t)((calib_a[19] << 8) | calib_a[18]);
    bme280_calib.dig_P8 = (int16_t)((calib_a[21] << 8) | calib_a[20]);
    bme280_calib.dig_P9 = (int16_t)((calib_a[23] << 8) | calib_a[22]);
    bme280_calib.dig_H1 = (uint8_t)(calib_a[25]);
}

/**
 * @brief Reads & stores second set of calibration coefficients
 *
 * Reads second set of calibration coefficients and stores them
 * in global bme280_calib_t variable.
 */
static void bme280_read_calib_b(void)
{
    twi_cfg_t read_calibb_cfg = {
        .dadr = BME280_ADDR,
        .iadr = CALIBB_ADDR,
        .iadr_size = TWI_ADDR_1BYTE
    };
    uint8_t calib_b[CALIBB_LEN];
    bme280_read_reg(&read_calibb_cfg, calib_b, CALIBB_LEN);

    /* Store calibration coefficients */
    bme280_calib.dig_H2 = (int16_t)((calib_b[1] << 8) | calib_b[0]);
    bme280_calib.dig_H3 = (uint8_t)(calib_b[2]);
    bme280_calib.dig_H4 = (int16_t)((calib_b[3] << 4) | (calib_b[4] & 0x0F));
    bme280_calib.dig_H5 = (int16_t)((calib_b[5] << 4) | (calib_b[4] >> 4));
    bme280_calib.dig_H6 = (int8_t)(calib_b[6]);
}

void bme280_init(void)
{
    /* Initialize & configure TWI peripheral for BME280 */
    twi_init();
    twi_cfg_t init_cfg = {
        .dadr = BME280_ADDR,
        .iadr = 0,
        .iadr_size = TWI_ADDR_0BYTE
    };
    twi_configure(&init_cfg);

    /* Send reset command for safe measure */
    uint8_t reset_cfg[2] = { RESET_ADDR, 0xB6 };
    twi_write(reset_cfg, sizeof(reset_cfg));

    /* Configure oversampling for pressure and temperature */
    uint8_t ctrlmeas_cfg[2] = { CTRLMEAS_ADDR, 0x27 };
    twi_write(ctrlmeas_cfg, sizeof(ctrlmeas_cfg));

    /* Read and store calibration coefficients for when compensating measurements */
    bme280_read_calib_a();
    bme280_read_calib_b();
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



uint32_t bme280_compensate_humidity(int32_t adc_humidity)
{
    int32_t v_x1_u32r;
    v_x1_u32r = (bme280_calib.t_fine - ((int32_t)76800));
    v_x1_u32r = (((((adc_humidity << 14) - (((int32_t)bme280_calib.dig_H4) << 20) - (((int32_t)bme280_calib.dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)bme280_calib.dig_H6)) >> 10) * (((v_x1_u32r * ((int32_t)bme280_calib.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) * ((int32_t)bme280_calib.dig_H2) + 8192) >> 14));
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)bme280_calib.dig_H1)) >> 4));
    v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);

    return (uint32_t)(v_x1_u32r>>12);
}

uint32_t bme280_compensate_pressure(int32_t adc_pressure)
{
    int64_t var1, var2, p;
    var1 = ((int64_t)bme280_calib.t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)bme280_calib.dig_P6;
    var2 = var2 + ((var1 * (int64_t)bme280_calib.dig_P5) << 17);
    var2 = var2 + (((int64_t)bme280_calib.dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)bme280_calib.dig_P3) >> 8) + ((var1 * (int64_t)bme280_calib.dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)bme280_calib.dig_P1) >> 33;

    if (var1 == 0)
        return 0; // avoid exception caused by division by zero

    p = 1048576 - adc_pressure;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)bme280_calib.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)bme280_calib.dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)bme280_calib.dig_P7) << 4);

    return (uint32_t)p;
}

int32_t bme280_compensate_temp(int32_t adc_temp)
{
    int32_t var1, var2;
    var1  = ((((adc_temp >> 3) - ((int32_t)bme280_calib.dig_T1 << 1))) * ((int32_t)bme280_calib.dig_T2)) >> 11;
    var2  = (((((adc_temp >> 4) - ((int32_t)bme280_calib.dig_T1)) * ((adc_temp >> 4) - ((int32_t)bme280_calib.dig_T1))) >> 12) * ((int32_t)bme280_calib.dig_T3)) >> 14;
    bme280_calib.t_fine = var1 + var2;

    return (bme280_calib.t_fine * 5 + 128) >> 8;
}


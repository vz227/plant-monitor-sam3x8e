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

void bme280_ctrl_meas(uint8_t* buffer)
{
    twi_msg_cfg_t ctrl_meas_msg = {
        .dadr = BME280_ADDR,
        .iadr = CTRLMEAS_ADDR,
        .iadr_size = TWI_ADDR_1BYTE
    };

    twi_msg_configure(&ctrl_meas_msg);
    twi_read(buffer, 1);
}

void bme280_read_id(uint8_t* buffer)
{
    twi_msg_cfg_t read_id_msg = {
        .dadr = BME280_ADDR,
        .iadr = ID_ADDR,
        .iadr_size = TWI_ADDR_1BYTE
    };

    twi_msg_configure(&read_id_msg);
    twi_read(buffer, ID_LEN);
}

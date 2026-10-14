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

static const twi_cfg_t bme280_cfg =
{
    .mode = TWI_MR_MODE,
    .dadr = 0x76,
    .iadr = 0xD0,
    .iadr_size = TWI_ADDR_1BYTE,
    .ckdiv = 1,
    .chdiv = 208,
    .cldiv = 208
};

static volatile uint8_t bme280_id;

void bme280_init()
{
    /* Initialize TWI0 */
    twi_init(&bme280_cfg);
    twi_read((uint8_t*)&bme280_id);
}



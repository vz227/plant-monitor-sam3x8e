/** @file bme280.h
 *  @brief Driver for the BME280 humidity & pressure sensor.
 *
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date October 8th, 2026
 */

#ifndef BME280_H
#define BME280_H

#include "twi.h"


/*================================
 * Addresses
 *================================*/

#define BME280_ADDR 0x76
#define HUM_ADDR    0xFD
#define TEMP_ADDR   0xFA
#define PRESS_ADDR  0xF7
#define CTRLMEAS_ADDR 0xF4
#define STATUS_ADDR 0xF3
#define RESET_ADDR  0xE0
#define CALIBB_ADDR 0xE1
#define ID_ADDR     0xD0
#define CALIBA_ADDR 0x88

/*================================
 * Length of Addresses (Regs Occupied)
 *================================*/

#define TEMP_LEN   3
#define STATUS_LEN 1
#define ID_LEN     1
#define CALIBA_LEN 26
#define CALIBB_LEN 7

/*================================
 * Calibration Coefficients
 *================================*/

typedef struct {
    uint16_t dig_T1;
    uint16_t dig_T2;
    uint16_t dig_T3;
} bme280_t;

/*================================
 * Function Declarations
 *================================*/

void bme280_init();
void bme280_read_temp(uint8_t* buffer);
void bme280_read_status(uint8_t* buffer);
void bme280_read_calib_a(uint8_t* buffer);
void bme280_read_calib_b(uint8_t* buffer);
int32_t bme280_compensate_humidity(uint8_t* adc_humidity);
int32_t bme280_compensate_pressure(uint8_t* adc_pressure);
int32_t bme280_compensate_temp(int32_t adc_temp);


#endif

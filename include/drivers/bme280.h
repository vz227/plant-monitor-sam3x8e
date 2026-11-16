/** @file bme280.h
 *  @brief Interface for BME280 driver.
 *
 * Contains functions for initializing the BME280, reading, and compensating
 * humidity, pressure, and temperature measurements.
 *
 * @author Vladimir Zhelev
 */

#ifndef BME280_H
#define BME280_H

#include "hal/twi.h"

/*================================
 * Addresses of important BME280 
 * registers
 *================================*/

#define BME280_ADDR   0x76
#define HUM_ADDR      0xFD
#define TEMP_ADDR     0xFA
#define PRESS_ADDR    0xF7
#define CTRLMEAS_ADDR 0xF4
#define STATUS_ADDR   0xF3
#define RESET_ADDR    0xE0
#define CALIBB_ADDR   0xE1
#define ID_ADDR       0xD0
#define CALIBA_ADDR   0x88

/*================================
 * Lengths of Addresses
 * (Regs Occupied)
 *================================*/

#define HUMIDITY_LEN    2
#define PRESSURE_LEN    3
#define TEMPERATURE_LEN 3
#define STATUS_LEN      1
#define ID_LEN          1
#define CALIBA_LEN      26
#define CALIBB_LEN      7

/*================================
 * Calibration Coefficients
 *================================*/

/**
 * @brief Calibration coefficients of BME280
 *
 * Holds calibration coefficients of BME280
 * to be used in measurement compensation
 * functions.
 */
typedef struct {
    uint8_t  dig_H1;
    int16_t  dig_H2;
    uint8_t  dig_H3;
    int16_t  dig_H4;
    int16_t  dig_H5;
    int8_t   dig_H6;
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;
    int32_t  t_fine;
} bme280_calib_t;

/*================================
 * Function Declarations
 *================================*/

/**
 * @brief BME280 initialization.
 *
 * Configures and initializes BME280 for reading measurements.
 */
void bme280_init(void);

/**
 * @brief Reads raw humidity.
 *
 * Reads uncompensated humidity measurement from BME280 register.
 *
 * @param buffer Buffer to store sensor measurement.
 */
void bme280_read_humidity(uint8_t* buffer);

/**
 * @brief Reads raw pressure.
 *
 * Reads uncompensated pressure measurement from BME280 register.
 *
 * @param buffer Buffer to store sensor measurement.
 */
void bme280_read_pressure(uint8_t* buffer);

/**
 * @brief Reads raw temperature.
 *
 * Reads uncompensated temperature measurement from BME280 register.
 *
 * @param buffer Buffer to store sensor measurement.
 */
void bme280_read_temp(uint8_t* buffer);

/**
 * @brief Reads BME280 status register.
 *
 * @param buffer Buffer to store status reading.
 */
void bme280_read_status(uint8_t* buffer);

/**
 * @brief Compensates raw humidity measurement from BME280.
 *
 * Takes raw ADC measurement from BME280 and converts it
 * to a human-readable value.
 *
 * @param adc_humidity Raw humidity measurement from BME280.
 * @return Compensated humidity in 1/1024 %RH .
 */
uint32_t bme280_compensate_humidity(int32_t adc_humidity);

/**
 * @brief Compensates raw pressure measurement from BME280.
 *
 * Takes raw ADC measurement from BME280 and converts it
 * to a human-readable value.
 *
 * @param adc_pressure Raw pressure measurement from BME280.
 * @return Compensated pressure in 1/256 Pa .
 */
uint32_t bme280_compensate_pressure(int32_t adc_pressure);

/**
 * @brief Compensates raw temperature measurement from BME280.
 *
 * Takes raw ADC measurement from BME280 and converts it
 * to a human-readable value.
 *
 * @param adc_temperature Raw temperature measurement from BME280.
 * @return Compensated temperature in 0.01°C.
 */
int32_t bme280_compensate_temp(int32_t adc_temp);


#endif

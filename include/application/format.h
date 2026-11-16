/** @file format.h
 *  @brief Formatting functions for sensor measurements.
 *
 * Contains functions for producing display-ready strings from raw sensor readings.
 *
 * @author Vladimir Zhelev
 */

#ifndef FORMAT_H
#define FORMAT_H

/*================================
 * Function Declarations
 *================================*/

/**
 * @brief Formats BME280 humidity reading for display.
 *
 * Converts compensated humidity value into a percentage string.
 *
 * @param val Compensated humidity measurement in units of 1/1024%RH.
 * @param buffer Destination buffer for formatted string.
 */
void format_humidity(uint32_t val, char* buffer);

/**
 * @brief Formats BME280 pressure reading for display.
 *
 * Converts compensated pressure value into a string containing pressure in hectopascals.
 *
 * @param val Compensated pressure measurement from BME280.
 * @param buffer Destination buffer for formatted string.
 */
void format_pressure(uint32_t val, char* buffer);

/**
 * @brief Formats BME280 temperature reading for display.
 *
 * Converts compensated temperature value into a string containing temperature in degrees Celsius.
 *
 * @param val Compensated temperature measurement in units of 0.01°C.
 * @param buffer Destination buffer for formatted string.
 */
void format_temp(int32_t val, char* buffer);

/**
 * @brief Formats EK1940 moisture reading for display.
 */
void format_moisture(uint16_t val, char* buffer);

#endif

/** @file sensors.h
 *  @brief High-level functions for retrieving sensor data.
 *
 * Contains wrapper functions for sensor drivers to retrieve
 * sensor measurements.
 *
 * @author Vladimir Zhelev
 */

#ifndef SENSORS_H
#define SENSORS_H

#include "drivers/bme280.h"
#include "drivers/ek1940.h"

/*================================
 * Type Definitions
 *================================*/

/**
 * @brief Stores sensor measurements.
 *
 * Stores sensor measurements in a global state that can be accessed from anywhere.
 */
typedef struct {
    uint32_t humidity;    // Humidity in units of 1/1024%RH
    uint32_t pressure;    // Pressure in hectopascals.
    int32_t  temperature; // Temperature in units of 0.01°C.
    uint16_t moisture;    // Moisture
} measurements_t;

/** @brief Global sensor measurement state. */
extern measurements_t sensor_data;

/*================================
 * Function Declarations
 *================================*/

/**
 * @brief Initializes sensor drivers.
 *
 * Wrapper to initialize all sensor drivers at once.
 */
void sensors_init(void);

/**
 * @brief Retrieves compensated humidity from BME280.
 *
 * Reads raw humidity measurement and processes it through sensor's
 * compensation algorithm, updating sensor_data.humidity.
 */
void read_humidity(void);

/**
 * @brief Retrieves compensated humidity from BME280.
 *
 * Reads raw pressure measurement and processes it through sensor's
 * compensation algorithm, updating sensor_data.pressure.
 */
void read_pressure(void);

/**
 * @brief Retrieves compensated temperature from BME280.
 *
 * Reads raw temperature measurement and processes it through sensor's
 * compensation algorithm, updating sensor_data.temperature.
 */
void read_temperature(void);


/**
 * @brief Retrieves moisture from EK1940.
 */
void read_moisture(void);

#endif

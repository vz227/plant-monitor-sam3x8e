/** @file sensors.h
 *  @brief Wrapper for sensor drivers to retrieve human-readable measurements.
 *
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date October 25th, 2026
 */

#include "bme280.h"

#ifndef SENSORS_H
#define SENSORS_H

typedef struct {
    uint32_t humidity;
    uint32_t pressure;
    int32_t  temperature;
} sensor_data_t;

extern sensor_data_t sensor_data;

/*================================
 * Function Declarations
 *================================*/

void sensors_init();
void read_humidity();
void read_pressure();
void read_temperature();

#endif

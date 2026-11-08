/** @file sensors.h
 *  @brief Wrapper for sensor drivers to retrieve human-readable measurements.
 *
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date October 25th, 2026
 */

#include "bme280.h"

/*================================
 * Function Declarations
 *================================*/

void sensors_init();
uint32_t read_humidity();
uint32_t read_pressure();
int32_t read_temperature();

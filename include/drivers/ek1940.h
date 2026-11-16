/** @file ek1940.h
 *  @brief Driver interface for the EK1940 soil moisture sensor
 *
 *  Contains functions for initializing the EK1940, and retrieving
 *  soil moisture.
 *
 *  @author Vladimir Zhelev
 */

#ifndef EK1940_H
#define EK1940_H

#include "hal/adc.h"

#define EK1940_DRY_VAL 3325
#define EK1940_WET_VAL 1450

/*================================
 * Function Declarations
 *================================*/

void ek1940_init(void);

void ek1940_read_moisture(uint16_t* buffer);

uint16_t ek1940_compensate_moisture(uint16_t adc_moisture);

#endif




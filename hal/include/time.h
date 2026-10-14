/** @file time.h
 *  @brief Module containing time/delay helper functions
 *
 *  Contains type definitions and function declarations
 *  related to timing.
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date July 31, 2026
 */

#ifndef TIME_H
#define TIME_H

#include <stdint.h>
#include "sam3xa.h"

/*================================
 * Function Declarations
 *================================*/

void delay_ms(uint32_t ms);
void delay_us(uint32_t us);
void wdt_disable();

#endif

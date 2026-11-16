/** @file tc.h
 *  @brief HAL interface for timer counter of SAM3X8E
 *
 *  Contains functions associated with hardware delay
 *  using internal timer counter peripheral.
 *
 *  @author Vladimir Zhelev
 */

#ifndef TC_H
#define TC_H

#include <stdint.h>
#include "sam3xa.h"

/*================================
 * Function Declarations
 *================================*/

/**
 * @brief Initializes TC0->Channel0
 *
 * Enables peripheral clock and configures
 * TC0->Channel0 to use internal MCK/2 clock
 */
void tc_init(void);


/**
 * @brief Creates a hardware delay in microseconds
 *
 * @param us Delay duration in microseconds.
 */
void tc_delay_us(uint32_t us);

/**
 * @brief Creates a hardware delay in milliseconds
 *
 * @param ms Delay duration in milliseconds.
 */
void tc_delay_ms(uint32_t ms);

/**
 * @brief Disables SAM3X8E watchdog timer
 *
 * Disables watchdog timer, as otherwise
 * MCU resets every ~16 seconds.
 */
void wdt_disable(void);

#endif

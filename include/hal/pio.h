/** @file pio.h
 *  @brief HAL interface for GPIO of SAM3X8E.
 *
 *  Configuration types and function declarations
 *  for GPIO HAL.
 *
 *  @author Vladimir Zhelev
 */

#ifndef PIO_H
#define PIO_H

#include "sam3xa.h"

/**
 * @brief PIO peripheral ID of SAM3X8E
 *
 * Indicates which PIO peripheral a pin
 * belongs to.
 */
typedef enum
{
    PIO_A = ID_PIOA,
    PIO_B = ID_PIOB,
    PIO_C = ID_PIOC,
    PIO_D = ID_PIOD
} pio_id_t;

/**
 * @brief PIO state
 *
 * Indicates whether a GPIO pin
 * is set or clear.
 */
typedef enum
{
    PIO_CLEAR = 0,
    PIO_SET = 1
} pio_state_t;

/**
 * @brief Initializes GPIO pin
 *
 * Initializes GPIO pin specified.
 *
 * @param pio_id Specifies PIO peripheral associated with pin.
 * @param pin Specifies pin number.
 */
void pio_init(const pio_id_t pio_id, const uint32_t pin);

/**
 * @brief Writes to GPIO pin
 *
 * Writes a particular pin to a specified GPIO pin.
 *
 * @param pio_id Specifies PIO peripheral associated with pin.
 * @param pin Specifies pin number.
 * @param state Specifies whether to clear or set pin.
 */
void pio_write(const pio_id_t pio_id, const uint32_t pin, const pio_state_t state);

#endif

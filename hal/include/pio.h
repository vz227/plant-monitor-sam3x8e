/** @file pio.h
 *  @brief HAL responsible for initializing and writing to GPIO
 *
 *  Contains type definitions and function declarations
 *  of the PIO HAL interface
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date August 3, 2026
 */

/*================================
 * Type Definitions
 *================================*/

#ifndef PIO_H
#define PIO_H

#include "sam3xa.h"

typedef enum
{
    PIO_INIT_SUCCESS,
    PIO_INIT_FAILURE,
    PIO_INVALID_ID,
    PIO_INVALID_PIN_ID
} pio_status_t;

typedef enum
{
    PIO_A = ID_PIOA,
    PIO_B = ID_PIOB,
    PIO_C = ID_PIOC,
    PIO_D = ID_PIOD
} pio_id_t;

typedef enum
{
    PIO_CLEAR = 0,
    PIO_SET = 1
} pio_state_t;

/*================================
 * Function Declarations
 *================================*/

pio_status_t pio_init(const pio_id_t pio_id, const uint32_t pin);
void pio_write(const pio_id_t pio_id, const uint32_t pin, const pio_state_t state);

#endif

/** @file pio.c
 *  @brief HAL responsible for initializing and writing to GPIO
 *
 *  Contains function implementations defined in pio.h.
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date August 3, 2026
 */

#include "pio.h"

pio_status_t pio_init(const pio_id_t pio_id, const uint32_t pin)
{
    /* Enable clock and set PIO Enable Register & PIO Output Enable Register */
    switch (pio_id)
    {
        case PIO_A:
            PMC->PMC_PCER0 |= (1u << pio_id);
            PIOA->PIO_PER |= (1u << pin);
            PIOA->PIO_OER |= (1u << pin);
            break;
        case PIO_B:
            PMC->PMC_PCER0 |= (1u << pio_id);
            PIOB->PIO_PER |= (1u << pin);
            PIOB->PIO_OER |= (1u << pin);
            break;
        case PIO_C:
            PMC->PMC_PCER0 |= (1u << pio_id);
            PIOC->PIO_PER |= (1u << pin);
            PIOC->PIO_OER |= (1u << pin);
            break;
        case PIO_D:
            PMC->PMC_PCER0 |= (1u << pio_id);
            PIOD->PIO_PER |= (1u << pin);
            PIOD->PIO_OER |= (1u << pin);
            break;
        default:
            return PIO_INVALID_ID;
    }

    return PIO_INIT_SUCCESS;
}

void pio_write(const pio_id_t pio_id, const uint32_t pin, const pio_state_t state)
{
    switch (pio_id)
    {
        case PIO_A:
            if (state == PIO_CLEAR)
                PIOA->PIO_CODR = (1u << pin);
            else
                PIOA->PIO_SODR = (1u << pin);
            break;
        case PIO_B:
            if (state == PIO_CLEAR)
                PIOB->PIO_CODR = (1u << pin);
            else
                PIOB->PIO_SODR = (1u << pin);
            break;
        case PIO_C:
            if (state == PIO_CLEAR)
                PIOC->PIO_CODR = (1u << pin);
            else
                PIOC->PIO_SODR = (1u << pin);
            break;
        case PIO_D:
            if (state == PIO_CLEAR)
                PIOD->PIO_CODR = (1u << pin);
            else
                PIOD->PIO_SODR = (1u << pin);
            break;
        default:
            return;
    }
}

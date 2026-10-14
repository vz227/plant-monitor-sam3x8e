/** @file time.c
 *  @brief Module containing time/delay helper functions
 *
 *  Contains function implementations declared in time.h
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date August 3, 2026
 */

#include "time.h"

void delay_ms(uint32_t ms)
{
    while (ms--)
        for (volatile uint32_t i = 0; i < 1000; i++);
}

void delay_us(uint32_t us)
{
    while (us--)
        for (volatile uint32_t i = 0; i < 10; i++);
}

void wdt_disable()
{
    WDT->WDT_MR |= WDT_MR_WDDIS;
}

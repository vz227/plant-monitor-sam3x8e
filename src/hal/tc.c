/** @file tc.c
 *  @brief HAL interface for timer counter of SAM3X8E
 *
 *  Contains implementations of functions associated with
 *  hardware delay using internal timer counter peripheral.
 *
 *  @author Vladimir Zhelev
 */

#include "hal/tc.h"

void tc_init(void)
{
    /* Enable clock for TC0 & configure 
     * TC0->Channel0 to use internal MCK/2 */
    PMC->PMC_PCER0 |= (1u << ID_TC0);
    TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_TCCLKS_TIMER_CLOCK1;

    /* Reset & start clock for TC0->Channel0 */
    TC0->TC_CHANNEL[0].TC_CCR = (TC_CCR_CLKEN | TC_CCR_SWTRG);
}

void tc_delay_us(uint32_t us)
{
    uint32_t start = TC0->TC_CHANNEL[0].TC_CV;
    uint32_t end = us * 42u;

    /* Spin until enough ticks have elapsed */
    while ((uint32_t)(TC0->TC_CHANNEL[0].TC_CV - start) < end);
}

void tc_delay_ms(uint32_t ms)
{
    uint32_t start = TC0->TC_CHANNEL[0].TC_CV;
    uint32_t end = ms * 42000u;

    /* Spin until enough ticks have elapsed */
    while ((uint32_t)(TC0->TC_CHANNEL[0].TC_CV - start) < end);
}

void wdt_disable(void)
{
    WDT->WDT_MR |= WDT_MR_WDDIS;
}

/** @file ek1940.c
 *  @brief Driver interface for the EK1940 soil moisture sensor
 *
 *  Contains implementations of functions for initializing the
 *  EK1940, and retrieving soil moisture.
 *
 *  @author Vladimir Zhelev
 */

#include "drivers/ek1940.h"

static const adc_cfg_t ek1940_cfg =
{
    .channel = 0,
    .prescaler = 3,
    .startup = ADC_STARTUP_0,
    .tracking_time = 0,
    .transfer_period = 0
};

void ek1940_init(void)
{

    adc_init(&ek1940_cfg);
}

void ek1940_read_moisture(uint16_t* buffer)
{
    adc_read(buffer, ek1940_cfg.channel);
}

uint16_t ek1940_compensate_moisture(uint16_t adc_moisture)
{
    if (adc_moisture >= EK1940_DRY_VAL)
        return 0;
    else if (adc_moisture <= EK1940_WET_VAL)
        return 10000;
    else
        return (((EK1940_DRY_VAL - adc_moisture) * 10000) / (EK1940_DRY_VAL - EK1940_WET_VAL)) ;
}

/** @file adc.h
 *  @brief HAL interface for analog-to-digital convertor of SAM3X8E
 *
 *  Contains type definitions and functions for the analog-to-digital
 *  convertor peripheral of the SAM3X8E.
 *
 *  @author Vladimir Zhelev
 */

#ifndef ADC_H
#define ADC_H

#include <stddef.h>
#include "sam3xa.h"

typedef enum {
    ADC_STARTUP_0   = ADC_MR_STARTUP_SUT0,
    ADC_STARTUP_8   = ADC_MR_STARTUP_SUT8,
    ADC_STARTUP_16  = ADC_MR_STARTUP_SUT16,
    ADC_STARTUP_24  = ADC_MR_STARTUP_SUT24,
    ADC_STARTUP_64  = ADC_MR_STARTUP_SUT64,
    ADC_STARTUP_80  = ADC_MR_STARTUP_SUT80,
    ADC_STARTUP_96  = ADC_MR_STARTUP_SUT96,
    ADC_STARTUP_112 = ADC_MR_STARTUP_SUT112,
    ADC_STARTUP_512 = ADC_MR_STARTUP_SUT512,
    ADC_STARTUP_576 = ADC_MR_STARTUP_SUT576,
    ADC_STARTUP_640 = ADC_MR_STARTUP_SUT640,
    ADC_STARTUP_704 = ADC_MR_STARTUP_SUT704,
    ADC_STARTUP_768 = ADC_MR_STARTUP_SUT768,
    ADC_STARTUP_832 = ADC_MR_STARTUP_SUT832,
    ADC_STARTUP_896 = ADC_MR_STARTUP_SUT896,
    ADC_STARTUP_960 = ADC_MR_STARTUP_SUT960
} adc_startup_t;

typedef struct {
    uint8_t       channel;
    uint8_t       prescaler;       /* ADCClock = MCK / ( (PRESCAL+1) * 2 ) */
    adc_startup_t startup;         /* Startup time in periods of ADC clock */
    uint8_t       tracking_time;   /* Tracking time = (TRACKTIM + 1) * ADCClock periods. */
    uint8_t       transfer_period; /* Transfer period = (TRANSFER * 2 + 3) ADCClock periods */
} adc_cfg_t;

/*================================
 * Function Declarations
 *================================*/

void adc_init(const adc_cfg_t* cfg);

void adc_read(uint16_t* buffer, uint8_t channel);

#endif

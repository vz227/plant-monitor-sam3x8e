/** @file adc.c
 *  @brief HAL interface for analog-to-digital convertor of SAM3X8E
 *
 *  Contains implementations of functions for the analog-to-digital
 *  convertor peripheral of the SAM3X8E.
 *
 *  @author Vladimir Zhelev
 */

#include "hal/adc.h"

static void adc_configure(const adc_cfg_t* cfg)
{
    /* Clear existing configuration */
    ADC->ADC_MR = 0;

    ADC->ADC_MR |= ADC_MR_PRESCAL(cfg->prescaler);
    ADC->ADC_MR |= cfg->startup;
    ADC->ADC_MR |= ADC_MR_TRACKTIM(cfg->tracking_time);
    ADC->ADC_MR |= ADC_MR_TRANSFER(cfg->transfer_period);
}

void adc_init(const adc_cfg_t* cfg)
{
    /* Enable clock for ADC & perform
     * software reset */
    PMC->PMC_PCER1 |= (1u << (ID_ADC - 32));
    ADC->ADC_CR = ADC_CR_SWRST;

    /* Hand control of pin A7 over to ADC peripheral */
    PIOA->PIO_PDR |= PIO_PDR_P2;

    /* Configure ADC mode register */
    adc_configure(cfg);

    /* Enable channel specified by configuration */
    ADC->ADC_CHER = (1u << cfg->channel);
}

void adc_read(uint16_t* buffer, const uint8_t channel)
{
    /* Start conversion */
    ADC->ADC_CR = ADC_CR_START;

    /* Wait for conversion to complete */
    while ((ADC->ADC_ISR & (1u << channel)) == 0);

    /* Write converted data into buffer */
    *buffer = ADC->ADC_CDR[channel];
}

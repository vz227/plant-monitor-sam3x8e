/** @file twi.c
 *  @brief HAL interface for TWI peripheral of SAM3X8E.
 *
 *  Function implementations for TWI HAL of
 *  SAM3X8E.
 *
 *  @author Vladimir Zhelev
 */

#include "hal/twi.h"
#include "sam3xa.h"

void twi_configure(const twi_cfg_t* cfg)
{
    /* Disable slave mode & enable master mode */
    TWI0->TWI_CR =
        TWI_CR_SVDIS |
        TWI_CR_MSEN;

    /* Configure internal address register if internal address of device exists */
    switch (cfg->iadr_size)
    {
        case TWI_ADDR_0BYTE:
            TWI0->TWI_MMR = TWI_MMR_IADRSZ_NONE;
            TWI0->TWI_IADR = 0;
            break;
        case TWI_ADDR_1BYTE:
            TWI0->TWI_MMR  = TWI_MMR_IADRSZ_1_BYTE;
            TWI0->TWI_IADR = TWI_IADR_IADR(cfg->iadr & 0x0000FF);
            break;
        case TWI_ADDR_2BYTE:
            TWI0->TWI_MMR  = TWI_MMR_IADRSZ_2_BYTE;
            TWI0->TWI_IADR = TWI_IADR_IADR(cfg->iadr & 0x00FFFF);
            break;
        case TWI_ADDR_3BYTE:
            TWI0->TWI_MMR  = TWI_MMR_IADRSZ_3_BYTE;
            TWI0->TWI_IADR = TWI_IADR_IADR(cfg->iadr);
            break;
    }

    TWI0->TWI_MMR |= TWI_MMR_DADR(cfg->dadr);
}

void twi_init()
{
    /* Enable clocks */
    PMC->PMC_PCER0 |= (1u << ID_PIOA);
    PMC->PMC_PCER0 |= (1u << ID_TWI0);

    /* Select Peripheral A functions for TWI0 pins
     * & give control of TWI0 pins to TWI0 peripheral */
    PIOA->PIO_ABSR &= ~TWI0_PINS;
    PIOA->PIO_PDR = TWI0_PINS;

    /* Configure clock */
    TWI0->TWI_CWGR =
    TWI_CWGR_CKDIV(TWI_CKDIV) |
    TWI_CWGR_CHDIV(TWI_CHDIV) |
    TWI_CWGR_CLDIV(TWI_CLDIV);
}

void twi_read(uint8_t* buffer, size_t len)
{
    /* Set Master Read */
    TWI0->TWI_MMR |= TWI_MMR_MREAD;

    /* Send START condition */
    TWI0->TWI_CR = TWI_CR_START;

    for (size_t i = 0; i < len; i++)
    {
        if (i == (len - 1))
            TWI0->TWI_CR = TWI_CR_STOP;

        while (!(TWI0->TWI_SR & TWI_SR_RXRDY));
        buffer[i] = TWI0->TWI_RHR;
    }

    while(!(TWI0->TWI_SR & TWI_SR_TXCOMP));
}

void twi_write(const uint8_t* buffer, size_t len)
{
    /* Set Master Write */
    TWI0->TWI_MMR &= ~TWI_MMR_MREAD;

    /* Send START condition */
    TWI0->TWI_CR = TWI_CR_START;

    /* Transmit message */
    for (size_t i = 0; i < len; i++)
    {
        while (!(TWI0->TWI_SR & TWI_SR_TXRDY));
        TWI0->TWI_THR = TWI_THR_TXDATA(buffer[i]);
    }

    TWI0->TWI_CR = TWI_CR_STOP;
    while(!(TWI0->TWI_SR & TWI_SR_TXCOMP));
}

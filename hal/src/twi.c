/** @file twi.c
 *  @brief HAL interface for TWI peripheral of SAM3X8E MCU
 *
 *  Contains function implementations declared in twi.h
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date September 25th, 2026
 */

#include "twi.h"
#include "sam3xa.h"

static void twi_configure(const twi_cfg_t* cfg)
{
    /* Configure master mode if selected */
    if (cfg->mode == TWI_MT_MODE  ||
        cfg->mode == TWI_MR_MODE  ||
        cfg->mode == TWI_MMT_MODE ||
        cfg->mode == TWI_MMR_MODE)
    {
        /* Configure internal address register if internal address of device exists */
        switch (cfg->iadr_size)
        {
            case TWI_ADDR_0BYTE:
                TWI0->TWI_MMR |= TWI_MMR_IADRSZ_NONE;
                break;
            case TWI_ADDR_1BYTE:
                TWI0->TWI_MMR  |= TWI_MMR_IADRSZ_1_BYTE;
                TWI0->TWI_IADR |= TWI_IADR_IADR(cfg->iadr & 0x0000FF);
                break;
            case TWI_ADDR_2BYTE:
                TWI0->TWI_MMR  |= TWI_MMR_IADRSZ_2_BYTE;
                TWI0->TWI_IADR |= TWI_IADR_IADR(cfg->iadr & 0x00FFFF);
                break;
            case TWI_ADDR_3BYTE:
                TWI0->TWI_MMR  |= TWI_MMR_IADRSZ_3_BYTE;
                TWI0->TWI_IADR |= TWI_IADR_IADR(cfg->iadr);
                break;
        }

        TWI0->TWI_MMR |= TWI_MMR_DADR(cfg->dadr);

        TWI0->TWI_CWGR = 
            TWI_CWGR_CKDIV(cfg->ckdiv) |
            TWI_CWGR_CHDIV(cfg->chdiv) |
            TWI_CWGR_CLDIV(cfg->cldiv);

        /* Disable slave mode & enable master mode */
        TWI0->TWI_CR = 
            TWI_CR_SVDIS |
            TWI_CR_MSEN;
    }

    else
    {
        TWI0->TWI_SMR |= TWI_SMR_SADR(cfg->dadr);
        TWI0->TWI_CR =
            TWI_CR_MSDIS |
            TWI_CR_SVEN;
    }
}

void twi_init(const twi_cfg_t* cfg)
{
    /* Enable clocks */
    PMC->PMC_PCER0 |= (1u << ID_PIOA);
    PMC->PMC_PCER0 |= (1u << ID_TWI0);

    PIOA->PIO_ABSR &= ~TWI0_PINS;
    PIOA->PIO_PDR = TWI0_PINS;

    twi_configure(cfg);
}

void twi_read(uint8_t* msg)
{
    /* Set Master Read */
    TWI0->TWI_MMR |= TWI_MMR_MREAD;

    /* Send START & STOP conditions for a single byte read */
    TWI0->TWI_CR |= (TWI_CR_START | TWI_CR_STOP);

    while (!(TWI0->TWI_SR & TWI_SR_RXRDY));

    *msg = TWI0->TWI_RHR;
}

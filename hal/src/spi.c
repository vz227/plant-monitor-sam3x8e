/** @file spi.c
 *  @brief HAL interface for SPI peripheral of SAM3X8E MCU.
 *
 *  Contains function implementations declared in spi.h
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date July 31, 2026
 */

#include "spi.h"
#include "sam3xa.h"


void spi_init(const spi_cfg_t* cfg)
{
    /* Enable clocks for PIOA and SPI0 */
    PMC->PMC_PCER0 |= (1u << ID_PIOA);
    PMC->PMC_PCER0 |= (1u << ID_SPI0);

    /* Select Peripheral A functions for SPI0 pins
     * & give control of SPI0 pins to SPI0 peripheral */
    PIOA->PIO_ABSR &= ~SPI0_PINS;
    PIOA->PIO_PDR = SPI0_PINS;

    /* Configure & Enable SPI0 */
    spi_configure(cfg);
    spi_enable();
}

void spi_enable()
{
    SPI0->SPI_CR = SPI_CR_SPIEN;
}

void spi_disable()
{
    SPI0->SPI_CR = SPI_CR_SPIDIS;
}

void spi_configure(const spi_cfg_t* cfg)
{
    /* Configure master/slave mode & chip select */
    SPI0->SPI_MR |= ((cfg->role == SPI_MASTER) ? SPI_MR_MSTR : 0);
    SPI0->SPI_MR |= (cfg->select_mode == SPI_FIXED_SELECT) ? SPI_MR_PCS(cfg->chip_select) : 0;

   /* Configure SPI mode */
    switch (cfg->mode) {
        case SPI_MODE_0:
            /* Set CPOL = 0, NCPHA = 1 */
            SPI0->SPI_CSR[cfg->chip_select] &= ~SPI_CSR_CPOL;
            SPI0->SPI_CSR[cfg->chip_select] |= SPI_CSR_NCPHA;
            break;
        case SPI_MODE_1:
            /* Set CPOL = 0, NCPHA = 0 */
            SPI0->SPI_CSR[cfg->chip_select] &= ~SPI_CSR_CPOL;
            SPI0->SPI_CSR[cfg->chip_select] &= ~SPI_CSR_NCPHA;
            break;
        case SPI_MODE_2:
            /* Set CPOL = 1, NCPHA = 1 */
            SPI0->SPI_CSR[cfg->chip_select] |= SPI_CSR_CPOL;
            SPI0->SPI_CSR[cfg->chip_select] |= SPI_CSR_NCPHA;
            break;
        case SPI_MODE_3:
            /* Set CPOL = 1, NCPHA = 0 */
            SPI0->SPI_CSR[cfg->chip_select] |= SPI_CSR_CPOL;
            SPI0->SPI_CSR[cfg->chip_select] &= ~SPI_CSR_NCPHA;
            break;
        default:
            return;
    }

    /* Configure bits per transfer & baud rate*/
    SPI0->SPI_CSR[cfg->chip_select] |= cfg->bits;
    SPI0->SPI_CSR[cfg->chip_select] |= SPI_CSR_SCBR(cfg->mck_divisor);
}

void spi_transfer(const void* tx, void* rx, size_t count, const spi_bits_t bits)
{
    /* Perform count transfers */
    for (size_t i = 0; i < count; ++i)
    {
        uint16_t tx_word = (bits == SPI_BITS_8)
                         ? ((const uint8_t*)tx)[i]
                         : ((const uint16_t*)tx)[i];
        while (!(SPI0->SPI_SR & SPI_SR_TDRE));

        SPI0->SPI_TDR = tx_word;

        while (!(SPI0->SPI_SR & SPI_SR_RDRF));

        /* If rx is null, ignore RDR contents */
        if (!rx)
        {
            SPI0->SPI_RDR;
            continue;
        }

        if (bits == SPI_BITS_8)
            ((uint8_t*)rx)[i] = SPI0->SPI_RDR;
        else
            ((uint16_t*)rx)[i] = SPI0->SPI_RDR;
    }
}


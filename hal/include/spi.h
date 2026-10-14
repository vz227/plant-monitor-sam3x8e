/** @file spi.h
 *  @brief HAL interface SPI peripheral of SAM3X8E MCU.
 *
 *  Contains type definitions and function declarations
 *  of the SPI HAL interface.
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date July 31, 2026
 */

#ifndef SPI_H
#define SPI_H

#include <stddef.h>
#include "sam3xa.h"

/*================================
 * Type Definitions
 *================================*/

typedef enum
{
    SPI_MASTER,
    SPI_SLAVE
} spi_role_t;

typedef enum
{
    SPI_FIXED_SELECT,
    SPI_VARIABLE_SELECT
} spi_select_mode_t;

typedef enum
{
    SPI_MODE_0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3
} spi_mode_t;

typedef enum
{
    SPI_BITS_8 = SPI_CSR_BITS_8_BIT,
    SPI_BITS_9 = SPI_CSR_BITS_9_BIT,
    SPI_BITS_10 = SPI_CSR_BITS_10_BIT,
    SPI_BITS_11 = SPI_CSR_BITS_11_BIT,
    SPI_BITS_12 = SPI_CSR_BITS_12_BIT,
    SPI_BITS_13 = SPI_CSR_BITS_13_BIT,
    SPI_BITS_14 = SPI_CSR_BITS_14_BIT,
    SPI_BITS_15 = SPI_CSR_BITS_15_BIT,
    SPI_BITS_16 = SPI_CSR_BITS_16_BIT
} spi_bits_t;

typedef struct
{
    spi_role_t          role;
    spi_mode_t          mode;
    spi_select_mode_t   select_mode;
    uint8_t             chip_select;
    spi_bits_t          bits;
    uint8_t             mck_divisor;
} spi_cfg_t;

/*================================
 * Macros
 *================================*/

/* SPI0 pin masks */
#define SPI0_MISO  (1 << 25)
#define SPI0_MOSI  (1 << 26)
#define SPI0_SPCK  (1 << 27)
#define SPI0_NPCS0 (1 << 28)
#define SPI0_NPCS1 (1 << 29)
#define SPI0_NPCS2 (1 << 30)
#define SPI0_NPCS3 (1 << 31)

/* Combined SPI0 pin mask */
#define SPI0_PINS (SPI0_MISO | SPI0_MOSI | SPI0_SPCK | SPI0_NPCS0 | SPI0_NPCS2 | SPI0_NPCS3)

/*================================
 * Function Declarations
 *================================*/

void spi_init(const spi_cfg_t* cfg);
void spi_enable();
void spi_disable();
void spi_enable_interrupts();
void spi_disable_interrupts();
void spi_configure(const spi_cfg_t* cfg);
void spi_transfer(const void* tx, void* rx, size_t count, const spi_bits_t bits);

#endif


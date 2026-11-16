/** @file spi.h
 *  @brief HAL interface for SPI peripheral of SAM3X8E.
 *
 *  Configuration types, pin masks, and function declarations
 *  for SPI HAL.
 *
 *  @author Vladimir Zhelev
 */

#ifndef SPI_H
#define SPI_H

#include <stddef.h>
#include "sam3xa.h"

/*================================
 * Type Definitions
 *================================*/

/**
 * @brief SPI operating role
 *
 * Specifies whether SPI peripheral operates
 * as a master or slave device.
 */
typedef enum
{
    SPI_MASTER,
    SPI_SLAVE
} spi_role_t;

/**
 * @brief SPI chip select mode
 *
 * Specifies whether peripheral uses fixed or variable
 * chip select.
 */
typedef enum
{
    SPI_FIXED_SELECT,
    SPI_VARIABLE_SELECT
} spi_select_mode_t;

/**
 * @brief SPI mode
 *
 * Determines clock idle state and which clock edge
 * is used to sample data. Corresponds to CPOL and CPHA
 * settings (2^2 = 4 possible modes).
 */
typedef enum
{
    SPI_MODE_0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3
} spi_mode_t;

/**
 * @brief SPI transfer data bit count
 *
 * Specifies how many bits are read and received
 * per SPI transfer.
 */
typedef enum
{
    SPI_BITS_8 =  SPI_CSR_BITS_8_BIT,
    SPI_BITS_9 =  SPI_CSR_BITS_9_BIT,
    SPI_BITS_10 = SPI_CSR_BITS_10_BIT,
    SPI_BITS_11 = SPI_CSR_BITS_11_BIT,
    SPI_BITS_12 = SPI_CSR_BITS_12_BIT,
    SPI_BITS_13 = SPI_CSR_BITS_13_BIT,
    SPI_BITS_14 = SPI_CSR_BITS_14_BIT,
    SPI_BITS_15 = SPI_CSR_BITS_15_BIT,
    SPI_BITS_16 = SPI_CSR_BITS_16_BIT
} spi_bits_t;

/**
 * @brief SPI peripheral configuration parameters
 *
 * Single data structure encapsulating the configuration
 * for a single SPI peripheral.
 */
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
 * SPI Pin Masks
 *
 * As per Arduino DUE specifications
 *================================*/

#define SPI0_MISO  (1u << 25)
#define SPI0_MOSI  (1u << 26)
#define SPI0_SPCK  (1u << 27)
#define SPI0_NPCS0 (1u << 28)
#define SPI0_NPCS1 (1u << 29)
#define SPI0_NPCS2 (1u << 30)
#define SPI0_NPCS3 (1u << 31)

#define SPI0_PINS (SPI0_MISO | SPI0_MOSI | SPI0_SPCK | SPI0_NPCS0 | SPI0_NPCS2 | SPI0_NPCS3)

/*================================
 * Function Declarations
 *================================*/

/**
 * @brief Initializes SPI0 peripheral of SAM3X8E.
 *
 * Enables peripheral clock & configures SPI0 pins.
 */
void spi_init(const spi_cfg_t* cfg);

/**
 * @brief Enables SPI0 peripheral of SAM3X8E.
 */
void spi_enable();

/**
 * @brief Disables SPI0 peripheral of SAM3X8E.
 */
void spi_disable();

/**
 * @brief Configures SPI0 peripheral of SAM3X8E.
 *
 * Configures SPI0 peripheral according to caller-provided
 * configuration file.
 *
 * @param cfg SPI configuration parameters.
 */
void spi_configure(const spi_cfg_t* cfg);

/**
 * @brief Performs a specified amount of SPI transfers.
 *
 * Transmits and receives data over SPI.
 *
 * @param tx Buffer containing data to be transmitted.
 * @param rx Buffer containing received data.
 * @param count Specifies the number of transfers to perform.
 * @param bits Specifies how many bits comprise each transfer.
 */
void spi_transfer(const void* tx, void* rx, size_t count, const spi_bits_t bits);

#endif

/** @file twi.h
 *  @brief HAL interface for TWI peripheral of SAM3X8E.
 *
 *  Configuration types, pin masks, and function declarations
 *  for TWI HAL.
 *
 *  @author Vladimir Zhelev
 */

#ifndef TWI_H
#define TWI_H

#include <stddef.h>
#include "sam3xa.h"

/**
 * @brief TWI internal address size
 *
 * Specifies size of internal address
 * of target device.
 */
typedef enum
{
    TWI_ADDR_0BYTE,
    TWI_ADDR_1BYTE,
    TWI_ADDR_2BYTE,
    TWI_ADDR_3BYTE
} twi_iadr_size_t;

/**
 * @brief TWI configuration parameters
 *
 * Structure encapsulating configuration used for
 * a single TWI/I^2C read/write operation.
 */
typedef struct
{
    uint32_t        dadr;      /* Target device address                           */
    uint32_t        iadr;      /* Internal address (address within target device) */
    twi_iadr_size_t iadr_size; /* Internal address size                           */
} twi_cfg_t;

/*================================
 * TWI Pin Masks
 *
 * As per Arduino DUE specifications
 *================================*/

#define TWI0_SCL   (1u << 18)
#define TWI0_SDA   (1u << 17)

#define TWI0_PINS (TWI0_SCL | TWI0_SDA)

/* Clock configuration */
#define TWI_CKDIV 1
#define TWI_CHDIV 208
#define TWI_CLDIV 208

/*================================
 * Function Declarations
 *================================*/

/**
 * @brief Initializes TWI0 peripheral of SAM3X8E.
 *
 * Enables peripheral clock & configures TWI0 pins.
 */
void twi_init();

/**
 * @brief Configures TWI0 peripheral of SAM3X8E.
 *
 * Sets target device address and internal address
 * configuration.
 *
 * @param cfg Pointer to TWI configuration parameters.
 */
void twi_configure(const twi_cfg_t* cfg);

/**
 * @brief Reads from TWI target device.
 *
 * @param buffer Buffer to store reading.
 * @param len Number of bytes to read into buffer.
 */
void twi_read(uint8_t* buffer, size_t len);

/**
 * @brief Writes to TWI target device.
 *
 * @param buffer Buffer to write to target device.
 * @param len Number of bytes to write.
 */
void twi_write(const uint8_t* buffer, size_t len);

#endif

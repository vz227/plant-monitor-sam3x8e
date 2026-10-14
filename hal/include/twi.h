/** @file twi.h
 *  @brief HAL interface TWI peripheral of SAM3X8E MCU.
 *
 *  Contains type definitions and function declarations
 *  of the TWI HAL interface.
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date September 9th, 2026
 */

#ifndef TWI_H
#define TWI_H

#include "sam3xa.h"

typedef enum
{
    TWI_MT_MODE,
    TWI_MR_MODE,
    TWI_MMT_MODE,
    TWI_MMR_MODE,
    TWI_ST_MODE,
    TWI_SR_MODE
} twi_mode_t;

typedef enum
{
    TWI_ADDR_0BYTE,
    TWI_ADDR_1BYTE,
    TWI_ADDR_2BYTE,
    TWI_ADDR_3BYTE
} twi_iadr_size_t;

typedef struct
{
    twi_mode_t      mode;
    uint32_t        dadr;
    uint32_t        iadr;
    twi_iadr_size_t iadr_size;
    uint8_t         ckdiv;
    uint8_t         chdiv;
    uint8_t         cldiv;
} twi_cfg_t;

/*================================
 * Macros
 *================================*/

/* TWI0 pin masks */
#define TWI0_SCL   (1 << 18)
#define TWI0_SDA   (1 << 17)

/* Combined TWI0 pin mask */
#define TWI0_PINS (TWI0_SCL | TWI0_SDA)

/*================================
 * Function Declarations
 *================================*/

void twi_init(const twi_cfg_t* cfg);
void twi_read(uint8_t* msg);

#endif

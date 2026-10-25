/** @file st7789.h
 *  @brief Driver for the ST7789 LCD controller.
 *
 *  Contains macros and function declarations for the
 *  ST7789 controller driver.
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date August 28, 2026
 */

#ifndef ST7789_H
#define ST7789_H

#include "spi.h"
#include "pio.h"
#include "time.h"

#define DISPLAY_WIDTH 0x00F0
#define DISPLAY_HEIGHT 0x0140

#define CS_PIN  17
#define DC_PIN  18
#define RST_PIN 19

/*================================
 * Function Declarations
 *================================*/

void st7789_init();
void st7789_clear(const uint16_t color);
void st7789_draw_glyph(const uint16_t xs, const uint16_t ys, const uint16_t glyph_width, const uint16_t glyph_height, const uint16_t fg_color, const uint16_t bg_color, const uint8_t* bitmap_data);

/*================================
 * ST7789 Command Macros
 *================================*/

#define NOP         0x00
#define SWRESET     0x01
#define RDDID       0x04
#define RDDST       0x09
#define RDDPM       0x0A
#define RDD_MADCTL  0x0B
#define RDD_COLMOD  0x0C
#define RDDIM       0x0D
#define RDDSM       0x0E
#define RDDSDR      0x0F
#define SLPIN       0x10
#define SLPOUT      0x11
#define PTLON       0x12
#define NORON       0x13
#define INVOFF      0x20
#define INVON       0x21
#define GAMSET      0x26
#define DISPOFF     0x28
#define DISPON      0x29
#define CASET       0x2A
#define RASET       0x2B
#define RAMWR       0x2C
#define RAMRD       0x2E
#define PTLAR       0x30
#define VSCRDEF     0x33
#define TEOFF       0x34
#define TEON        0x35
#define MADCTL      0x36
#define VSCRSADD    0x37
#define IDMOFF      0x38
#define IDMON       0x39
#define COLMOD      0x3A
#define RAMWRC      0x3C
#define RAMRDC      0x3E
#define TESCAN      0x44
#define RDTESCAN    0x45
#define WRDISBV     0x51
#define RDDISBV     0x52
#define WRCTRLD     0x53
#define RDCTRLD     0x54
#define WRCACE      0x55
#define RDCABC      0x56
#define WRCABCMB    0x5E
#define RDCABCMB    0x5F
#define RDABCSDR    0x68
#define RDID1       0xDA
#define RDID2       0xDB
#define RDID3       0xDC
#define RAMCTRL     0xB0
#define RGBCTRL     0xB1
#define PORCTRL     0xB2
#define FRCTRL1     0xB3
#define GCTRL       0xB7
#define DGMEN       0xBA
#define VCOMS       0xBB
#define LCMCTRL     0xC0
#define IDSET       0xC1
#define VDVVRHEN    0xC2
#define VRHS        0xC3
#define VDVSET      0xC4
#define VCMOFSET    0xC5
#define FRCTRL2     0xC6
#define CABCCTRL    0xC7
#define REGSEL1     0xC8
#define REGSEL2     0xCA
#define PWMFRSEL    0xCC
#define PWCTRL1     0xD0
#define VAPVANEN    0xD2
#define CMD2EN      { 0xDF, 0x5A, 0x69, 0x02 }
#define PVGAMCTRL   0xE0
#define NVGAMCTRL   0xE1
#define DGMLUTR     0xE2
#define DGMLUTB     0xE3
#define GATECTRL    0xE4
#define PWCTRL2     0xE8
#define EQCTRL      0xE9
#define PROMCTRL    0xEC
#define PROMEN      0xFA
#define NVMSET      0xFC
#define PROMACT     0xFE

/*================================
 * ST7789 Initialization Parameters
 *================================*/

static const uint8_t madctl_init[]    = { 0xC0 };
static const uint8_t colmod_init[]    = { 0x05 };
static const uint8_t caset_init[]     = { 0x00, 0x01, 0x00, 0x3F };
static const uint8_t raset_init[]     = { 0x00, 0x00, 0x00, 0xEF };
static const uint8_t porctrl_init[]   = { 0x0C, 0x0C, 0x00, 0x33, 0x33 };
static const uint8_t gctrl_init[]     = { 0x35 };
static const uint8_t vcoms_init[]     = { 0x1F };
static const uint8_t lcmctrl_init[]   = { 0x2C };
static const uint8_t vdvvrhen_init[]  = { 0x01 };
static const uint8_t vrhs_init[]      = { 0x12 };
static const uint8_t vdvset_init[]    = { 0x20 };
static const uint8_t frctrl2_init[]   = { 0x0F };
static const uint8_t pwctrl1_init[]   = { 0xA4, 0xA1 };
static const uint8_t pvgamctrl_init[] = { 0xD0, 0x08, 0x11, 0x08, 0x0C, 0x15, 0x39, 0x33, 0x50, 0x36, 0x13, 0x14, 0x29, 0x2D };
static const uint8_t nvgamctrl_init[] = { 0xD0, 0x08, 0x10, 0x08, 0x06, 0x06, 0x39, 0x44, 0x51, 0x0B, 0x16, 0x14, 0x2F, 0x31, 0x21 };

#endif

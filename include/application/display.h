/** @file display.h
 *  @brief High-level display abstraction functions for ST7789 display controller.
 *
 * Contains wrapper functions to display sensor measurements through ST7789 display driver.
 *
 * @author Vladimir Zhelev
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "drivers/st7789.h"
#include "application/sensors.h"

/*================================
 * General display & font
 * configuration parameters
 *================================*/

/** Background and foreground colours */
#define BG_COLOR 0x0821
#define FG_COLOR 0xBDF7

/** Glyph parameters */
#define GLYPH_WIDTH 6
#define GLYPH_HEIGHT 12

/** Column and row counts calculated using glyph dimensions */
#define COLS (DISPLAY_WIDTH/GLYPH_WIDTH)
#define ROWS (DISPLAY_HEIGHT/GLYPH_HEIGHT)

/*================================
 * Row/Column Coordinates
 *
 * CS: Column Start
 * RS: Row Start
 * CE: Column End
 * RE: Row End
 *================================*/

#define TITLE_CS 8
#define TITLE_RS 1
#define TITLE_CE 32
#define TITLE_RE 2

#define HUMIDITY_CS 8
#define HUMIDITY_RS 4
#define HUMIDITY_CE 32
#define HUMIDITY_RE 5

#define PRESSURE_CS 8
#define PRESSURE_RS 5
#define PRESSURE_CE 32
#define PRESSURE_RE 6

#define TEMPERATURE_CS 8
#define TEMPERATURE_RS 6
#define TEMPERATURE_CE 32
#define TEMPERATURE_RE 7

#define MOISTURE_CS 8
#define MOISTURE_RS 7
#define MOISTURE_CE 32
#define MOISTURE_RE 8

/*================================
 * Function Declarations
 *================================*/

/**
 * @brief Initializes, clears, and draws title on display.
 *
 * Initializes ST7789 driver, fills the screen with BG_COLOR, and displays title of application.
 */
void display_init(void);

/**
 * @brief Draws humidity measurement from BME280.
 *
 * Reads and formats humidity measurement from BME280, and displays measurement on screen.
 */
void display_humidity(void);

/**
 * @brief Draws pressure measurement from BME280.
 *
 * Reads and formats pressure measurement from BME280, and displays measurement on screen.
 */
void display_pressure(void);

/**
 * @brief Draws temperature measurement from BME280.
 *
 * Reads and formats temperature measurement from BME280, and displays measurement on screen.
 */
void display_temperature(void);

/**
 * @brief Draws moisture measurement from EK1940.
 *
 * Reads and formats moisture measurement from EK1940, and displays measurement on screen.
 */
void display_moisture(void);

/*================================
 * Font Definition
 *================================*/

/**
 * @brief Bitmap representation of character glyph.
 *
 * Stores data for a single 8x12 glyph.
 */
typedef struct {
    uint8_t pixel_data[12];
} glyph_t;

/**
 * @brief Bitmap font containing 128 ASCII glyphs.
 *
 * Each row of each glyph is comprised of 1 byte, with each glyph comprising of 12 rows.
 */
static const glyph_t font[128] = {
    [' '] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00
        }
    },
    ['_'] = {
        .pixel_data = {
            0x00,
            0xFC,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00
        }
    },
    ['%'] = {
        .pixel_data = {
            0x00,
            0x40,
            0xA0,
            0xA8,
            0x50,
            0x20,
            0x50,
            0xA8,
            0x28,
            0x10,
            0x00,
            0x00
        }
    },
    ['+'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x20,
            0x20,
            0xF8,
            0x20,
            0x20,
            0x00,
            0x00,
            0x00,
            0x00
        }
    },
    ['-'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0xF8,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00
        }
    },
    ['.'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x60,
            0x60,
            0x00,
            0x00,
            0x00
        }
    },
    [':'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x60,
            0x60,
            0x00,
            0x00,
            0x60,
            0x60,
            0x00,
            0x00,
            0x00
        }
    },
    ['a'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x70,
            0x08,
            0x78,
            0x88,
            0x78,
            0x00,
            0x00,
            0x00
        }
    },
    ['b'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x80,
            0x80,
            0xF0,
            0x88,
            0x88,
            0x88,
            0xF0,
            0x00,
            0x00,
            0x00
        }
    },
    ['c'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x78,
            0x80,
            0x80,
            0x80,
            0x78,
            0x00,
            0x00,
            0x00
        }
    },
    ['d'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x08,
            0x08,
            0x78,
            0x88,
            0x88,
            0x88,
            0x78,
            0x00,
            0x00,
            0x00
        }
    },
    ['e'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x70,
            0x88,
            0xF8,
            0x80,
            0x78,
            0x00,
            0x00,
            0x00
        }
    },
    ['f'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x38,
            0x40,
            0xF8,
            0x40,
            0x40,
            0x40,
            0x40,
            0x00,
            0x00,
            0x00
        }
    },
    ['g'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x78,
            0x88,
            0x88,
            0x88,
            0x78,
            0x08,
            0x70,
            0x00
        }
    },
    ['h'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x80,
            0x80,
            0xF0,
            0x88,
            0x88,
            0x88,
            0x88,
            0x00,
            0x00,
            0x00
        }
    },
    ['i'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x20,
            0x00,
            0x60,
            0x20,
            0x20,
            0x20,
            0x70,
            0x00,
            0x00,
            0x00
        }
    },
    ['j'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x10,
            0x00,
            0x30,
            0x10,
            0x10,
            0x10,
            0x10,
            0x10,
            0x60,
            0x00
        }
    },
    ['k'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x80,
            0x80,
            0x90,
            0xA0,
            0xE0,
            0x90,
            0x88,
            0x00,
            0x00,
            0x00
        }
    },
    ['l'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x60,
            0x20,
            0x20,
            0x20,
            0x20,
            0x20,
            0x70,
            0x00,
            0x00,
            0x00
        }
    },
    ['m'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0xD8,
            0xA8,
            0xA8,
            0xA8,
            0xA8,
            0x00,
            0x00,
            0x00
        }
    },
    ['n'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0xF0,
            0x88,
            0x88,
            0x88,
            0x88,
            0x00,
            0x00,
            0x00
        }
    },
    ['o'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x70,
            0x88,
            0x88,
            0x88,
            0x70,
            0x00,
            0x00,
            0x00
        }
    },
    ['p'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0xF0,
            0x88,
            0x88,
            0x88,
            0xF0,
            0x80,
            0x80,
            0x00
        }
    },
    ['q'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x78,
            0x88,
            0x88,
            0x88,
            0x78,
            0x08,
            0x08,
            0x00
        }
    },
    ['r'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0xB8,
            0xC0,
            0x80,
            0x80,
            0x80,
            0x00,
            0x00,
            0x00
        }
    },
    ['s'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x78,
            0x80,
            0x70,
            0x08,
            0xF0,
            0x00,
            0x00,
            0x00
        }
    },
    ['t'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x40,
            0xF8,
            0x40,
            0x40,
            0x40,
            0x38,
            0x00,
            0x00,
            0x00
        }
    },
    ['u'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x88,
            0x88,
            0x88,
            0x88,
            0x78,
            0x00,
            0x00,
            0x00
        }
    },
    ['v'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x88,
            0x88,
            0x88,
            0x50,
            0x20,
            0x00,
            0x00,
            0x00
        }
    },
    ['w'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x88,
            0x88,
            0xA8,
            0xA8,
            0xD8,
            0x00,
            0x00,
            0x00
        }
    },
    ['x'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x88,
            0x50,
            0x20,
            0x50,
            0x88,
            0x00,
            0x00,
            0x00
        }
    },
    ['y'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0x88,
            0x88,
            0x50,
            0x50,
            0x20,
            0x20,
            0xC0,
            0x00
        }
    },
    ['z'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x00,
            0x00,
            0xF8,
            0x10,
            0x20,
            0x40,
            0xF8,
            0x00,
            0x00,
            0x00
        }
    },
    ['A'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x20,
            0x50,
            0x88,
            0x88,
            0xF8,
            0x88,
            0x88,
            0x00,
            0x00,
            0x00
        }
    },
    ['B'] = {
        .pixel_data = {
            0x00,
            0x00,
            0xF0,
            0x88,
            0x88,
            0xF0,
            0x88,
            0x88,
            0xF0,
            0x00,
            0x00,
            0x00
        }
    },
    ['C'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x38,
            0x40,
            0x80,
            0x80,
            0x80,
            0x40,
            0x38,
            0x00,
            0x00,
            0x00
        }
    },
    ['D'] = {
        .pixel_data = {
            0x00,
            0x00,
            0xF0,
            0x88,
            0x88,
            0x88,
            0x88,
            0x90,
            0xE0,
            0x00,
            0x00,
            0x00
        }
    },
    ['E'] = {
        .pixel_data = {
            0x00,
            0x00,
            0xF8,
            0x80,
            0x80,
            0xF0,
            0x80,
            0x80,
            0xF8,
            0x00,
            0x00,
            0x00
        }
    },
    ['F'] = {
        .pixel_data = {
            0x00,
            0x00,
            0xF8,
            0x80,
            0x80,
            0xF0,
            0x80,
            0x80,
            0x80,
            0x00,
            0x00,
            0x00
        }
    },
    ['G'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x38,
            0x40,
            0x80,
            0x98,
            0x88,
            0x48,
            0x38,
            0x00,
            0x00,
            0x00
        }
    },
    ['H'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x88,
            0x88,
            0x88,
            0xF8,
            0x88,
            0x88,
            0x88,
            0x00,
            0x00,
            0x00
        }
    },
    ['I'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x70,
            0x20,
            0x20,
            0x20,
            0x20,
            0x20,
            0x70,
            0x00,
            0x00,
            0x00
        }
    },
    ['J'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x08,
            0x08,
            0x08,
            0x08,
            0x88,
            0x88,
            0x70,
            0x00,
            0x00,
            0x00
        }
    },
    ['K'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x88,
            0x90,
            0xA0,
            0xC0,
            0xA0,
            0x90,
            0x88,
            0x00,
            0x00,
            0x00
        }
    },
    ['L'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x80,
            0x80,
            0x80,
            0x80,
            0x80,
            0x80,
            0xF8,
            0x00,
            0x00,
            0x00
        }
    },
    ['M'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x88,
            0xD8,
            0xA8,
            0xA8,
            0x88,
            0x88,
            0x88,
            0x00,
            0x00,
            0x00
        }
    },
    ['N'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x88,
            0xC8,
            0xA8,
            0x98,
            0x88,
            0x88,
            0x88,
            0x00,
            0x00,
            0x00
        }
    },
    ['O'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x70,
            0x88,
            0x88,
            0x88,
            0x88,
            0x88,
            0x70,
            0x00,
            0x00,
            0x00
        }
    },
    ['P'] = {
        .pixel_data = {
            0x00,
            0x00,
            0xF0,
            0x88,
            0x88,
            0xF0,
            0x80,
            0x80,
            0x80,
            0x00,
            0x00,
            0x00
        }
    },
    ['Q'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x70,
            0x88,
            0x88,
            0x88,
            0x88,
            0x88,
            0x70,
            0x10,
            0x08,
            0x00
        }
    },
    ['R'] = {
        .pixel_data = {
            0x00,
            0x00,
            0xF0,
            0x88,
            0x88,
            0xF0,
            0xA0,
            0x90,
            0x88,
            0x00,
            0x00,
            0x00
        }
    },
    ['S'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x78,
            0x80,
            0x80,
            0x70,
            0x08,
            0x08,
            0xF0,
            0x00,
            0x00,
            0x00
        }
    },
    ['T'] = {
        .pixel_data = {
            0x00,
            0x00,
            0xF8,
            0x20,
            0x20,
            0x20,
            0x20,
            0x20,
            0x20,
            0x00,
            0x00,
            0x00
        }
    },
    ['U'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x88,
            0x88,
            0x88,
            0x88,
            0x88,
            0x88,
            0x70,
            0x00,
            0x00,
            0x00
        }
    },
    ['V'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x88,
            0x88,
            0x88,
            0x50,
            0x50,
            0x20,
            0x20,
            0x00,
            0x00,
            0x00
        }
    },
    ['W'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x88,
            0x88,
            0x88,
            0xA8,
            0xA8,
            0xA8,
            0xD8,
            0x00,
            0x00,
            0x00
        }
    },
    ['X'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x88,
            0x88,
            0x50,
            0x20,
            0x50,
            0x88,
            0x88,
            0x00,
            0x00,
            0x00
        }
    },
    ['Y'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x88,
            0x88,
            0x50,
            0x20,
            0x20,
            0x20,
            0x20,
            0x00,
            0x00,
            0x00
        }
    },
    ['Z'] = {
        .pixel_data = {
            0x00,
            0x00,
            0xF8,
            0x10,
            0x20,
            0x20,
            0x40,
            0x40,
            0xF8,
            0x00,
            0x00,
            0x00
        }
    },
    ['0'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x70,
            0x88,
            0x98,
            0xA8,
            0xC8,
            0x88,
            0x70,
            0x00,
            0x00,
            0x00
        }
    },
    ['1'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x20,
            0x60,
            0xA0,
            0x20,
            0x20,
            0x20,
            0xF8,
            0x00,
            0x00,
            0x00
        }
    },
    ['2'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x70,
            0x88,
            0x08,
            0x10,
            0x20,
            0x40,
            0xF8,
            0x00,
            0x00,
            0x00
        }
    },
    ['3'] = {
        .pixel_data = {
            0x00,
            0x00,
            0xF8,
            0x08,
            0x10,
            0x30,
            0x08,
            0x88,
            0x70,
            0x00,
            0x00,
            0x00
        }
    },
    ['4'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x10,
            0x30,
            0x50,
            0x90,
            0xF8,
            0x10,
            0x10,
            0x00,
            0x00,
            0x00
        }
    },
    ['5'] = {
        .pixel_data = {
            0x00,
            0x00,
            0xF8,
            0x80,
            0xF0,
            0x08,
            0x08,
            0x88,
            0x70,
            0x00,
            0x00,
            0x00
        }
    },
    ['6'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x30,
            0x40,
            0x80,
            0xF0,
            0x88,
            0x88,
            0x70,
            0x00,
            0x00,
            0x00
        }
    },
    ['7'] = {
        .pixel_data = {
            0x00,
            0x00,
            0xF8,
            0x08,
            0x10,
            0x10,
            0x20,
            0x20,
            0x20,
            0x00,
            0x00,
            0x00
        }
    },
    ['8'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x70,
            0x88,
            0x88,
            0x70,
            0x88,
            0x88,
            0x70,
            0x00,
            0x00,
            0x00
        }
    },
    ['9'] = {
        .pixel_data = {
            0x00,
            0x00,
            0x70,
            0x88,
            0x88,
            0x78,
            0x08,
            0x10,
            0x60,
            0x00,
            0x00,
            0x00
        }
    }
};

#endif

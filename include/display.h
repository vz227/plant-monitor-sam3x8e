/** @file display.h
 *  @brief Display interface of plant monitor application layer
 *
 *
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date September 16th, 2026
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "st7789.h"

/*================================
 * Display Parameters
 *================================*/

#define BG_COLOR 0x0821
#define FG_COLOR 0xBDF7

#define GLYPH_WIDTH 6
#define GLYPH_HEIGHT 12

#define COLS (DISPLAY_WIDTH/GLYPH_WIDTH)
#define ROWS (DISPLAY_HEIGHT/GLYPH_HEIGHT)

/*================================
 * Row/Column Coordinates of Display Regions
 *================================*/

#define HUMIDITY_CS 8
#define HUMIDITY_RS 2
#define HUMIDITY_CE 32
#define HUMIDITY_RE 3

#define PRESSURE_CS 8
#define PRESSURE_RS 3
#define PRESSURE_CE 32
#define PRESSURE_RE 4

#define TEMPERATURE_CS 8
#define TEMPERATURE_RS 4
#define TEMPERATURE_CE 32
#define TEMPERATURE_RE 5

/*================================
 * Function Declarations
 *================================*/

void display_init();
void display_clear();
void display_text(const char* str, uint8_t col, uint8_t row);

/*================================
 * Font Definition
 *================================*/

typedef struct {
    uint8_t pixel_data[12];
} glyph_t;

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


/** @file display.c
 *  @brief Text rendering interface for ST7789 display driver.
 *
 *  Contains function implementations from display.h
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date September 16th, 2026
 */

#include "display.h"

void display_init()
{
    st7789_init();
}

void display_msg(char* str, const uint8_t col, const uint8_t row)
{
    for (uint8_t i = 0; str[i] != '\0'; i++)
    {
        st7789_draw_glyph(
            ((col + i) * GLYPH_WIDTH),
            (row * GLYPH_HEIGHT),
            GLYPH_WIDTH,
            GLYPH_HEIGHT,
            FG_COLOR, BG_COLOR,
            font[(uint8_t)str[i]].pixel_data
        );
    }
}

void display_clear()
{
    st7789_draw_rectangle(0, DISPLAY_WIDTH, 0, DISPLAY_HEIGHT, BG_COLOR);
}

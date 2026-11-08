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
#include "convert.h"

static void display_text(const char* str, uint8_t col, uint8_t row)
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

void display_init()
{
    st7789_init();
    st7789_clear(BG_COLOR);
}

void display_title()
{
    static const char title[] = "plant monitor sam3x8e";
    display_text(title, TITLE_CS, TITLE_RS);
}

void display_humidity()
{
    read_humidity();
    char hum_str[8];
    int32_str((int32_t)sensor_data.humidity, hum_str);
    display_text(hum_str, HUMIDITY_CS, HUMIDITY_RS);
}

void display_pressure()
{
    read_pressure();
    char press_str[8];
    int32_str((int32_t)sensor_data.pressure, press_str);
    display_text(press_str, PRESSURE_CS, PRESSURE_RS);
}

void display_temperature()
{
    read_temperature();
    char temp_str[8];
    int32_str(sensor_data.temperature, temp_str);
    display_text(temp_str, TEMPERATURE_CS, TEMPERATURE_RS);
}

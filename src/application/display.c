/** @file display.c
 *  @brief High-level display abstraction functions for ST7789 display controller.
 *
 * Contains implementations of wrapper functions to display sensor measurements
 * through ST7789 driver.
 *
 *  @author Vladimir Zhelev
 */

#include "application/display.h"
#include "application/format.h"

/**
 * @brief Renders a string on the display.
 *
 * Displays string starting at the specified row
 * and column coordinates.
 */
static void display_text(const char* str, uint8_t col, uint8_t row)
{
    for (size_t i = 0; str[i] != '\0'; i++)
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

/**
 * @brief Renders title of the application.
 */
static void display_title(void)
{
    static const char title[] = "Plant Monitor SAM3X8E";
    display_text(title, TITLE_CS, TITLE_RS);
    display_text("_____________________", TITLE_CS, TITLE_RS + 1);
}

void display_init(void)
{
    st7789_init();
    st7789_clear(BG_COLOR);
    display_title();
}

void display_humidity(void)
{
    read_humidity();

    char hum_str[16];
    format_humidity(sensor_data.humidity, hum_str);

    display_text("Humidity: ", HUMIDITY_CS, HUMIDITY_RS);
    display_text(hum_str, HUMIDITY_CS + 15, HUMIDITY_RS);
}

void display_pressure(void)
{
    read_pressure();

    char press_str[16];
    format_pressure(sensor_data.pressure, press_str);

    display_text("Pressure: ", PRESSURE_CS, PRESSURE_RS);
    display_text(press_str, PRESSURE_CS + 15, PRESSURE_RS);
}

void display_temperature(void)
{
    read_temperature();

    char temp_str[16];
    format_temp(sensor_data.temperature, temp_str);

    display_text("Temp: ", TEMPERATURE_CS, TEMPERATURE_RS);
    display_text(temp_str, TEMPERATURE_CS + 15, TEMPERATURE_RS);
}

void display_moisture(void)
{
    read_moisture();

    char moisture_str[16];
    format_moisture(sensor_data.moisture, moisture_str);

    display_text("Moisture: ", MOISTURE_CS, MOISTURE_RS);
    display_text(moisture_str, MOISTURE_CS + 15, MOISTURE_RS);
}

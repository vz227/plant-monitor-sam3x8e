/** @file main.c
 *  @brief Main loop of plant monitor application
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date August 31, 2026
 */

#include "display.h"
#include "st7789.h"
#include "bme280.h"

int main()
{
    display_init();
    display_clear();

    uint8_t temp_buffer[3];
    uint8_t status_buffer = 0;
    uint8_t id_buffer = 0;
    uint8_t ctrl_meas_buffer = 0;

    bme280_init();
    bme280_read_temp(temp_buffer);
    bme280_ctrl_meas(&ctrl_meas_buffer);
    bme280_read_status(&status_buffer);
    bme280_read_id(&id_buffer);

    st7789_draw_rectangle(20, 30, 20, 32, 0xAC51);
    st7789_draw_rectangle(30, 40, 20, 32, 0x8D51);
    st7789_draw_rectangle(40, 50, 20, 32, 0xAD51);
    st7789_draw_rectangle(50, 60, 20, 32, 0x8C55);
    st7789_draw_rectangle(60, 70, 20, 32, 0xAC55);
    st7789_draw_rectangle(70, 80, 20, 32, 0x8D55);

    display_msg("hello world", 12, 12);
    display_msg("example plant temperature", 12, 13);
    display_msg("1234567890", 12, 14);

    while (1);
}

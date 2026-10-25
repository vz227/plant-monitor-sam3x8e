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
    sensors_init();

    bme280_read_temp(temp_buffer);
    bme280_ctrl_meas(&ctrl_meas_buffer);
    bme280_read_status(&status_buffer);
    bme280_read_id(&id_buffer);

    display_text("hello world", 12, 12);
    display_text("example plant temperature", 12, 13);
    display_text("1234567890", 12, 14);

    while (1);
}

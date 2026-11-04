/** @file main.c
 *  @brief Main loop of plant monitor application
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date August 31, 2026
 */

#include "display.h"
#include "sensors.h"
#include "FreeRTOS.h"

int main()
{
    display_init();
    sensors_init();

    display_title();
    display_temperature();

    while (1);
}

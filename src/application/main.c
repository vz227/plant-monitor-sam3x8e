/** @file main.c
 *  @brief Application entry point
 *
 * Initializes display, sensors, and tasks, and
 * runs indefinitely.
 *
 * @author Vladimir Zhelev
 */

#include "application/display.h"
#include "application/sensors.h"
#include "application/tasks.h"

int main(void)
{
    /* Initialize components */
    display_init();
    sensors_init();
    tasks_init();

    /* Let tasks run indefinitely */
    for (;;);
}

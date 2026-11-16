/** @file tasks.c
 *  @brief Task functions to be run by FreeRTOS.
 *
 * Contains implementations of task functions and
 * task initialization functions to be used alongside
 * FreeRTOS.
 *
 * @author Vladimir Zhelev
 */

#include "application/tasks.h"
#include "application/display.h"

void humidity_task(void* params)
{
    for (;;)
    {
        display_humidity();
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    vTaskDelete(NULL);
}

void pressure_task(void* params)
{
    for (;;)
    {
        display_pressure();
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    vTaskDelete(NULL);
}

void temperature_task(void* params)
{
    for (;;)
    {
        display_temperature();
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    vTaskDelete(NULL);
}

void moisture_task(void* params)
{
    for (;;)
    {
        display_moisture();
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    vTaskDelete(NULL);
}

void tasks_init(void)
{
    static StackType_t humidity_stack[TASK_STACK_SIZE];
    static StackType_t pressure_stack[TASK_STACK_SIZE];
    static StackType_t temperature_stack[TASK_STACK_SIZE];
    static StackType_t moisture_stack[TASK_STACK_SIZE];

    static StaticTask_t humidity_tcb;
    static StaticTask_t pressure_tcb;
    static StaticTask_t temperature_tcb;
    static StaticTask_t moisture_tcb;

    xTaskCreateStatic(humidity_task, "Humidity Task", TASK_STACK_SIZE, NULL, 1, humidity_stack, &humidity_tcb);
    xTaskCreateStatic(pressure_task, "Pressure Task", TASK_STACK_SIZE, NULL, 1, pressure_stack, &pressure_tcb);
    xTaskCreateStatic(temperature_task, "Temperature Task", TASK_STACK_SIZE, NULL, 1, temperature_stack, &temperature_tcb);
    xTaskCreateStatic(moisture_task, "Moisture Task", TASK_STACK_SIZE, NULL, 1, moisture_stack, &moisture_tcb);

    vTaskStartScheduler();
}

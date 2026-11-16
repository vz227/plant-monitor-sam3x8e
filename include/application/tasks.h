/** @file tasks.h
 *  @brief Task functions to be run by FreeRTOS.
 *
 * Contains task functions and task initialization functions
 * to be used alongside FreeRTOS.
 *
 * @author Vladimir Zhelev
 */

#ifndef TASKS_H
#define TASKS_H

#include "FreeRTOS.h"
#include "task.h"

/*================================
 * Task configuration parameters
 *================================*/

/** Number of stack layers to be used for sensor tasks */
#define TASK_STACK_SIZE 256

/*================================
 * Function Declarations
 *================================*/

/**
 * @brief Humidity task for FreeRTOS.
 *
 * Retrieves and displays humidity in an infinite loop. Scheduled by FreeRTOS
 * @param params Unused task parameter required by function signature of a FreeRTOS task function.
 */
void humidity_task(void* params);

/**
 * @brief Pressure task for FreeRTOS.
 *
 * Retrieves and displays pressure in an infinite loop. Scheduled by FreeRTOS
 * @param params Unused task parameter required by function signature of a FreeRTOS task function.
 */
void pressure_task(void* params);

/**
 * @brief Temperature task for FreeRTOS.
 *
 * Retrieves and displays temperature in an infinite loop. Scheduled by FreeRTOS
 * @param params Unused task parameter required by function signature of a FreeRTOS task function.
 */
void temperature_task(void* params);


/**
 * @brief Moisture task for FreeRTOS.
 *
 * Retrieves and displays moisture in an infinite loop. Scheduled by FreeRTOS
 * @param params Unused task parameter required by function signature of a FreeRTOS task function.
 */
void moisture_task(void* params);

/**
 * @brief Creates FreeRTOS tasks and starts the scheduler.
 *
 * Creates sensor tasks using statically allocated task control blocks
 * and stack memory.
 */
void tasks_init(void);

#endif

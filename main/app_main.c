/*
 * app_main.c
 *
 *  Created on: 19-Jul-2025
 *      Author: vivek
 *
 *  Description:
 *      Main entry point for ESP32 Indicator System.
 *      Initializes drivers and sets up scheduler with separate Base and Application tasks.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "gpio_driver.h"
#include "pwm_driver.h"
#include "indicator_app.h"
#include "hw_timer_driver.h"

// Scheduler interval for both tasks (100 milliseconds)
#define SCHEDULER_PERIOD_MS 100

// Task handles
TaskHandle_t base_task_handle = NULL;
TaskHandle_t app_task_handle = NULL;

/**
 * @brief Base task (runs background base-layer driver functions)
 */
void base_task(void *arg)
{
    while (1)
    {
        // Placeholder for base-layer operations (if any)
        vTaskDelay(pdMS_TO_TICKS(SCHEDULER_PERIOD_MS));
    }
}

/**
 * @brief Application task (handles app-level logic)
 */
void application_task(void *arg)
{
    while (1)
    {
        // Run indicator state machine and LED logic
        indicator_app_update();
        vTaskDelay(pdMS_TO_TICKS(SCHEDULER_PERIOD_MS));
    }
}

/**
 * @brief Main entry point called by ESP-IDF runtime.
 */
void app_main(void)
{
    printf("Starting Indicator System...\n");

    // Initialize low-level hardware drivers
    gpio_driver_init();
    pwm_driver_init();
    indicator_app_init();

    // Launch scheduler tasks (base + application)
    xTaskCreate(base_task, "base_task", 2048, NULL, 5, &base_task_handle);
    xTaskCreate(application_task, "app_task", 4096, NULL, 5, &app_task_handle);
}





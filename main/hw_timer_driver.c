/*
 * hw_timer_driver.c
 *
 *  Created on: 19-Jul-2025
 *      Author: vivek
 *
 *  Description:
 *      Implementation of hardware timer driver (1-second one-shot timer)
 *      for button hold detection on ESP32 using Timer Group peripheral.
 */

#include "hw_timer_driver.h"
#include "driver/timer.h"
#include "esp_log.h"

#define TIMER_GROUP            TIMER_GROUP_0
#define TIMER_IDX              TIMER_0
#define TIMER_DIVIDER          80         // 80 MHz / 80 = 1 MHz (1 tick = 1 µs)
#define TIMER_INTERVAL_SEC     1.0        // 1 second

static const char *TAG = "HW_TIMER";

// Internal flags and callback
static bool timer_running = false;
static timer_callback_t user_callback = NULL;

// Public flag to indicate ISR trigger
volatile bool isr_fired = false;

/**
 * @brief ISR callback function triggered after 1 second.
 */
static bool IRAM_ATTR timer_isr_callback(void *args)
{
    timer_running = false;
    timer_pause(TIMER_GROUP, TIMER_IDX);  // Stop the timer (one-shot)
    isr_fired = true;

    if (user_callback) {
        user_callback();  // Call user-defined callback (e.g. mark button as held)
    }

    return true;  // Return true to automatically clear interrupt
}

/**
 * @brief Configure the hardware timer and register ISR callback.
 */
void hw_timer_init(timer_callback_t cb)
{
    user_callback = cb;

    timer_config_t config = {
        .divider = TIMER_DIVIDER,
        .counter_dir = TIMER_COUNT_UP,
        .counter_en = TIMER_PAUSE,
        .alarm_en = TIMER_ALARM_EN,
        .auto_reload = false,  // One-shot timer
    };

    timer_init(TIMER_GROUP, TIMER_IDX, &config);
    timer_set_counter_value(TIMER_GROUP, TIMER_IDX, 0);
    timer_set_alarm_value(TIMER_GROUP, TIMER_IDX, TIMER_INTERVAL_SEC * 1000000);  // 1 sec
    timer_enable_intr(TIMER_GROUP, TIMER_IDX);
    timer_isr_callback_add(TIMER_GROUP, TIMER_IDX, timer_isr_callback, NULL, 0);

    ESP_LOGI(TAG, "Hardware timer initialized");
}

/**
 * @brief Start the hardware timer (if not already running).
 */
void hw_timer_start(void)
{
    if (!timer_running) {
        ESP_LOGI(TAG, "Starting Timer");

        timer_set_counter_value(TIMER_GROUP, TIMER_IDX, 0);
        timer_set_alarm_value(TIMER_GROUP, TIMER_IDX, TIMER_INTERVAL_SEC * 1000000);  // 1 sec
        timer_set_alarm(TIMER_GROUP, TIMER_IDX, TIMER_ALARM_EN);
        timer_enable_intr(TIMER_GROUP, TIMER_IDX);
        timer_start(TIMER_GROUP, TIMER_IDX);

        timer_running = true;
    }
}

/**
 * @brief Stop and reset the timer (if running).
 */
void hw_timer_stop(void)
{
    if (timer_running) {
        ESP_LOGI(TAG, "Stopping Timer");

        timer_pause(TIMER_GROUP, TIMER_IDX);
        timer_set_counter_value(TIMER_GROUP, TIMER_IDX, 0);
        timer_disable_intr(TIMER_GROUP, TIMER_IDX);

        timer_running = false;
    }
}

/**
 * @brief Returns whether the timer is active.
 */
bool hw_timer_is_running(void)
{
    return timer_running;
}






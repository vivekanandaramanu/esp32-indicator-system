/*
 * hw_timer_driver.h
 *
 *  Created on: 19-Jul-2025
 *      Author: vivek
 *
 *  Description:
 *      Header file for one-shot hardware timer driver on ESP32.
 *      Used to detect 1-second button hold events through ISR-based timing.
 */

#ifndef HW_TIMER_DRIVER_H_
#define HW_TIMER_DRIVER_H_

#include <stdbool.h>

/**
 * @brief Function pointer type for the timer callback.
 */
typedef void (*timer_callback_t)(void);

/**
 * @brief Initialize hardware timer with a user callback.
 * 
 * @param cb  Callback function to be called after 1 second.
 */
void hw_timer_init(timer_callback_t cb);

/**
 * @brief Start the hardware timer for 1 second.
 */
void hw_timer_start(void);

/**
 * @brief Stop the hardware timer and reset state.
 */
void hw_timer_stop(void);

/**
 * @brief Check if the timer is currently running.
 * 
 * @return true if timer is active, false otherwise.
 */
bool hw_timer_is_running(void);

/**
 * @brief Flag set by ISR to indicate timer expiry.
 */
extern volatile bool isr_fired;

#endif // HW_TIMER_DRIVER_H_

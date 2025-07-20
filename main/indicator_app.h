/*
 * indicator_app.h
 *
 *  Created on: 19-Jul-2025
 *      Author: vivek
 *
 *  Description:
 *      Application interface for controlling the indicator system.
 *      Defines indicator modes and declares initialization and update functions.
 */

#ifndef INDICATOR_APP_H
#define INDICATOR_APP_H

#include <pwm_driver.h>
#include "driver/ledc.h"

/**
 * @brief Enum for indicator operation modes.
 */
typedef enum {
    INDICATOR_OFF = 0,   ///< No indicator is active
    INDICATOR_LEFT,      ///< Left indicator blinking
    INDICATOR_RIGHT,     ///< Right indicator blinking
    INDICATOR_HAZARD     ///< Both indicators blinking
} indicator_mode_t;

/**
 * @brief Initialize the indicator application.
 *        Should be called once during startup.
 */
void indicator_app_init(void);

/**
 * @brief Periodic update function for application logic.
 *        Call every 100ms (scheduler period).
 */
void indicator_app_update(void);

// LEDC channels assigned for PWM control
#define LEFT_LED_CHANNEL   LEDC_CHANNEL_A
#define RIGHT_LED_CHANNEL  LEDC_CHANNEL_B

#endif // INDICATOR_APP_H


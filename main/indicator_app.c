/*
 * indicator_app.c
 *
 *  Created on: 19-Jul-2025
 *      Author: vivek
 *
 *  Description:
 *      This file contains the core application logic for controlling
 *      left, right, and hazard indicator behavior based on push button events.
 */

#include "indicator_app.h"
#include "gpio_driver.h"
#include "pwm_driver.h"
#include "freertos/FreeRTOS.h"
#include <stdbool.h>
#include "hw_timer_driver.h"
#include "esp_log.h"

// String mapping for modes (used in UART logs)
static const char* mode_str[] = {
    "OFF",              // 0
    "LEFT INDICATOR",   // 1
    "RIGHT INDICATOR",  // 2
    "HAZARD MODE"       // 3
};

static const char *TAG = "INDICATOR";

// Flags set from ISR when button held for 1 sec
static volatile bool left_held_event = false;
static volatile bool right_held_event = false;

// Forward declarations
static void update_led_pwm(indicator_mode_t mode, bool led_state);
static void indicator_button_hold_handler(void);

// State tracking
static bool prev_left = false;
static bool prev_right = false;
static volatile indicator_mode_t current_mode = INDICATOR_OFF;
static uint8_t blink_timer = 0;
static bool led_state = false;

/**
 * @brief Initializes the application logic and hardware timer.
 */
void indicator_app_init(void)
{
    current_mode = INDICATOR_OFF;
    blink_timer = 0;
    led_state = false;

    hw_timer_init(indicator_button_hold_handler);  // Register timer ISR
}

/**
 * @brief Main state machine update function. Call every 100ms.
 */
void indicator_app_update(void)
{
    bool curr_left = is_left_button_pressed();
    bool curr_right = is_right_button_pressed();

    // Detect rising edge (fresh button press)
    bool left_edge = curr_left && !prev_left;
    bool right_edge = curr_right && !prev_right;

    // Handle new press
    if (left_edge || right_edge) {
        ESP_LOGI(TAG, "Button Press Detected");
        if (left_edge) printf("[UART] Left Button Pressed\n");
        if (right_edge) printf("[UART] Right Button Pressed\n");

        if (!hw_timer_is_running())
            hw_timer_start();

    } else if (!curr_left && !curr_right) {
        hw_timer_stop();  // Stop timer only if both buttons are released
    }

    // Update state for next cycle
    prev_left = curr_left;
    prev_right = curr_right;

    // ISR fired (optional debug log)
    if (isr_fired) {
        ESP_LOGI(TAG, "ISR Callback Fired!");
        isr_fired = false;
    }

    // Handle events from 1-sec hold
    if (left_held_event || right_held_event) {
        bool left = left_held_event;
        bool right = right_held_event;
        left_held_event = false;
        right_held_event = false;

        // Hazard mode: both buttons held
        if (left && right) {
            ESP_LOGI(TAG, "Both Buttons Held -> Toggling Hazard");
            current_mode = (current_mode == INDICATOR_HAZARD) ? INDICATOR_OFF : INDICATOR_HAZARD;
            printf("[UART] Both Buttons Held for 1s. Mode: HAZARD ON\n");
            return;
        }

        // Exit hazard mode if only one held
        if (current_mode == INDICATOR_HAZARD) {
            ESP_LOGI(TAG, "Exiting Hazard Mode");
            current_mode = INDICATOR_OFF;
            printf("[UART] Hazard Mode OFF\n");
            return;
        }

        // Regular toggle for individual buttons
        if (left) {
            ESP_LOGI(TAG, "Left Button Held");
            current_mode = (current_mode == INDICATOR_LEFT) ? INDICATOR_OFF : INDICATOR_LEFT;
            printf("[UART] Left Button Held for 1s. Mode: %s\n",
                   current_mode == INDICATOR_LEFT ? "LEFT INDICATOR ON" : "LEFT INDICATOR OFF");

        } else if (right) {
            ESP_LOGI(TAG, "Right Button Held");
            current_mode = (current_mode == INDICATOR_RIGHT) ? INDICATOR_OFF : INDICATOR_RIGHT;
            printf("[UART] Right Button Held for 1s. Mode: %s\n",
                   current_mode == INDICATOR_RIGHT ? "RIGHT INDICATOR ON" : "RIGHT INDICATOR OFF");
        }
    }

    // Blinking logic: toggle LED every 300ms when active
    if (current_mode != INDICATOR_OFF) {
        blink_timer++;
        if (blink_timer >= 3) {  // 3 * 100ms = 300ms
            blink_timer = 0;
            led_state = !led_state;
            update_led_pwm(current_mode, led_state);
        }
    } else {
        update_led_pwm(INDICATOR_OFF, false);  // Ensure both LEDs off
    }
}

/**
 * @brief Sets PWM duty for LEDs based on current mode and state.
 */
static void update_led_pwm(indicator_mode_t mode, bool led_state)
{
    uint32_t duty = led_state ? 4095 : 0;

    switch (mode) {
        case INDICATOR_LEFT:
            pwm_set_duty(LEFT_LED_CHANNEL, duty);
            pwm_set_duty(RIGHT_LED_CHANNEL, 0);
            printf("[UART] LED Status: %s  | Mode: %s\n", led_state ? "ON" : "OFF", mode_str[mode]);
            break;

        case INDICATOR_RIGHT:
            pwm_set_duty(RIGHT_LED_CHANNEL, duty);
            pwm_set_duty(LEFT_LED_CHANNEL, 0);
            printf("[UART] LED Status: %s  | Mode: %s\n", led_state ? "ON" : "OFF", mode_str[mode]);
            break;

        case INDICATOR_HAZARD:
            pwm_set_duty(LEFT_LED_CHANNEL, duty);
            pwm_set_duty(RIGHT_LED_CHANNEL, duty);
            printf("[UART] LED Status: %s  | Mode: %s\n", led_state ? "ON" : "OFF", mode_str[mode]);
            break;

        default:
            pwm_set_duty(LEFT_LED_CHANNEL, 0);
            pwm_set_duty(RIGHT_LED_CHANNEL, 0);
            break;
    }
}

/**
 * @brief ISR callback for hardware timer (1 sec hold detection).
 */
static void indicator_button_hold_handler(void)
{
    if (is_left_button_pressed() && is_right_button_pressed()) {
        left_held_event = true;
        right_held_event = true;
    } else if (is_left_button_pressed()) {
        left_held_event = true;
    } else if (is_right_button_pressed()) {
        right_held_event = true;
    }
}






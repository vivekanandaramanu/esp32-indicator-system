/*
 * gpio_driver.c
 *
 *  Created on: 18-Jul-2025
 *      Author: vivek
 *
 *  Description:
 *      Source file for GPIO driver module.
 *      Implements initialization and input reading logic.
 */

#include "gpio_driver.h"
#include "driver/gpio.h"

// Define GPIO numbers for LEDs and buttons
#define LEFT_BUTTON_GPIO    GPIO_NUM_14
#define RIGHT_BUTTON_GPIO   GPIO_NUM_4
#define LEFT_LED_GPIO       GPIO_NUM_17
#define RIGHT_LED_GPIO      GPIO_NUM_16

/**
 * @brief Initialize GPIOs for LEDs and buttons.
 */
void gpio_driver_init(void)
{
    // Configure LED pins as OUTPUT
    gpio_config_t led_config = {
        .pin_bit_mask = (1ULL << LEFT_LED_GPIO) | (1ULL << RIGHT_LED_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = 0,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&led_config);

    // Configure button pins as INPUT with pull-up
    gpio_config_t btn_config = {
        .pin_bit_mask = (1ULL << LEFT_BUTTON_GPIO) | (1ULL << RIGHT_BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = 1,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&btn_config);
}

/**
 * @brief Check if left button is pressed.
 * @return true if pressed, false if released.
 */
bool is_left_button_pressed(void)
{
    return gpio_get_level(LEFT_BUTTON_GPIO) == 0;  // Active-low logic
}

/**
 * @brief Check if right button is pressed.
 * @return true if pressed, false if released.
 */
bool is_right_button_pressed(void)
{
    return gpio_get_level(RIGHT_BUTTON_GPIO) == 0;  // Active-low logic
}






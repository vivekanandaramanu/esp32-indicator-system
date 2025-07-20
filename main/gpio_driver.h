/*
 * gpio_driver.h
 *
 *  Created on: 18-Jul-2025
 *      Author: vivek
 *
 *  Description:
 *      Header file for GPIO driver module.
 *      Provides interfaces to initialize GPIOs for LEDs and buttons,
 *      and to read button states.
 */

#ifndef MAIN_GPIO_DRIVER_H_
#define MAIN_GPIO_DRIVER_H_

#include <stdbool.h>

/**
 * @brief Initialize GPIOs for LEDs and push buttons.
 *
 * Configures:
 * - LEFT and RIGHT LED pins as OUTPUT.
 * - LEFT and RIGHT push button pins as INPUT with pull-ups.
 */
void gpio_driver_init(void);

/**
 * @brief Read state of left button.
 * @return true if pressed (active-low), false otherwise.
 */
bool is_left_button_pressed(void);

/**
 * @brief Read state of right button.
 * @return true if pressed (active-low), false otherwise.
 */
bool is_right_button_pressed(void);

#endif /* MAIN_GPIO_DRIVER_H_ */


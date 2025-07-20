/*
 * pwm_driver.h
 *
 *  Created on: 19-Jul-2025
 *      Author: vivek
 *
 *  Description:
 *      Header file for PWM driver to control LED brightness using ESP32 LEDC peripheral.
 */

#ifndef MAIN_PWM_DRIVER_H_
#define MAIN_PWM_DRIVER_H_

#include <stdint.h>

// PWM Configuration Macros
#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_HIGH_SPEED_MODE
#define LEDC_OUTPUT_IO_1        (17)  // GPIO for Left LED
#define LEDC_OUTPUT_IO_2        (16)  // GPIO for Right LED
#define LEDC_CHANNEL_A          LEDC_CHANNEL_0
#define LEDC_CHANNEL_B          LEDC_CHANNEL_1
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT   // 13-bit resolution (0–8191)
#define LEDC_FREQUENCY          (1000)              // 1 kHz frequency

/**
 * @brief Initialize PWM channels and timer for controlling LEDs.
 */
void pwm_driver_init(void);

/**
 * @brief Set the PWM duty cycle for a given LED channel.
 * 
 * @param channel   LEDC channel (LEDC_CHANNEL_A or LEDC_CHANNEL_B)
 * @param duty      Duty cycle (0 to 8191 for 13-bit resolution)
 */
void pwm_set_duty(uint8_t channel, uint32_t duty);

#endif /* MAIN_PWM_DRIVER_H_ */


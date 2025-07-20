
/*
 * pwm_driver.c
 *
 *  Created on: 19-Jul-2025
 *      Author: vivek
 *
 *  Description:
 *      Source file for PWM driver using ESP32 LEDC module.
 *      Used to control left and right indicator LEDs via PWM.
 */

#include "pwm_driver.h"
#include "driver/ledc.h"
#include "esp_err.h"

/**
 * @brief Initialize the LEDC PWM timer and channels.
 */
void pwm_driver_init(void)
{
    // Configure LEDC timer
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // Configure LEFT LED (GPIO 17) → LEDC_CHANNEL_A
    ledc_channel_config_t ledc_channel1 = {
        .speed_mode     = LEDC_HIGH_SPEED_MODE,
        .channel        = LEDC_CHANNEL_A,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO_1,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel1);

    // Configure RIGHT LED (GPIO 16) → LEDC_CHANNEL_B
    ledc_channel_config_t ledc_channel2 = {
        .speed_mode     = LEDC_HIGH_SPEED_MODE,
        .channel        = LEDC_CHANNEL_B,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO_2,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel2);
}

/**
 * @brief Set duty cycle for the given LEDC channel.
 *
 * @param channel   PWM channel to update
 * @param duty      Duty value (0–8191 for 13-bit resolution)
 */
void pwm_set_duty(uint8_t channel, uint32_t duty)
{
    ledc_set_duty(LEDC_MODE, channel, duty);
    ledc_update_duty(LEDC_MODE, channel);
}



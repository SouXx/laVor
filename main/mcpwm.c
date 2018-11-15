/*
 * mcpwm.c
 *
 *  Created on: Nov 9, 2018
 *      Author: tobi
 * This code is part of the LaVOR system application. Please see the license.txt
 * file for further information.
 *
 * The code is licensed under the
 *
 * 		Creative Commmons Attribution-NonCommercial-ShareAlike 4.0 International License.
 *
 * You are free to use this code for non-commercial applications as long as you leave this
 * attribution included in all copies or substantial portions of the Software.
 *
 * Authors: Tobias Frahm, Philipp Haenyes, Joschka Sondhof, Josefine Palm, Malte Rejzek
 */
#include "mcpwm.h"

void
pwm_init (void)
{
  uint32_t num_of_pulse = 0;

  mcpwm_config_t mcpwm_config =
    { .frequency = PWM_FREQUENCY, .cmpr_a = 50.0, .duty_mode =
	MCPWM_DUTY_MODE_1, .counter_mode = MCPWM_UP_COUNTER };

  ESP_ERROR_CHECK_WITHOUT_ABORT (
      mcpwm_gpio_init (MCPWM_UNIT_0, MCPWM0A, MOTOR_PWM_OUT_PIN));
  ESP_ERROR_CHECK_WITHOUT_ABORT (
      mcpwm_init (MCPWM_UNIT_0, MCPWM0A, &mcpwm_config));
  ESP_ERROR_CHECK_WITHOUT_ABORT (
      mcpwm_capture_enable (MCPWM_UNIT_0, MCPWM_SELECT_CAP_PIN, MCPWM_POS_EDGE,
			    num_of_pulse));
}


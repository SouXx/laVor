/*
 * mcpwm.c
 *
 *  Created on: Nov 9, 2018
 *      Author: Tobias Frahm
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
	  mcpwm_pin_config_t pin_config = {
		        .mcpwm0a_out_num = MOTOR_PWM_OUT_PIN,
		        //.mcpwm_cap0_in_num   = ENCODER_A,
		    };
		    mcpwm_set_pin(MCPWM_UNIT_0, &pin_config);


		    //printf("Configuring Initial Parameters of mcpwm...\n");
		    mcpwm_config_t pwm_config;
		    pwm_config.frequency = PWM_FREQUENCY;    //frequency of Motor
		    pwm_config.cmpr_a = 0.0;       //duty cycle Motor
		    pwm_config.counter_mode = MCPWM_UP_COUNTER;
		    pwm_config.duty_mode = MCPWM_DUTY_MODE_1;
		    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);   //Configure PWM0A & PWM0B with above settings



		    //2. Capture configuration
		    /*
		     mcpwm_capture_enable(MCPWM_UNIT_0, MCPWM_SELECT_CAP0, MCPWM_POS_EDGE, 20);  //capture signal on rising edge, prescale = 10 i.e. 8,000,000 counts is equal to one second
		    MCPWM->int_ena.val = BIT(27);  //Enable interrupt on  CAP0 in Interrupt-Status-Register
		    mcpwm_isr_register(MCPWM_UNIT_0, capture_isr_handler, NULL, ESP_INTR_FLAG_IRAM, NULL);  //Set ISR Handler
	*/
}


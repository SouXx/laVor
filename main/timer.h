/*
 * timer.h
 *MOST CODE IS BASED ON EXAMPLES FROM https://github.com/espressif/esp-idf
 *  Created on: Nov 15, 2018
 *      Author: Malte Rejzek
 *
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

#ifndef MAIN_TIMER_H_
#define MAIN_TIMER_H_

#include <stdio.h>
#include "esp_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "soc/gpio_sig_map.h"
#include "soc/timer_group_struct.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"
#include "driver/pcnt.h"
#include "system_config.h"



xQueueHandle timer_queue;



struct controller_evt_t {
	int16_t count1;
	int16_t count2;
	uint64_t angle_timer;
	int t_count;
};


void IRAM_ATTR timer0_isr(void *para);
void IRAM_ATTR timer1_isr(void *para);

// Controller Timer
void timer1_init(void);
// Timer for Angle Setpoit
void timer0_init(void);






#endif /* MAIN_TIMER_H_ */

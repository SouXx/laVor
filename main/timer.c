/*
 * timer.c
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

#include "timer.h"
//static const char* TAG = "Timer";

int timercount = 0;
int led_count = 0;


void IRAM_ATTR timer0_isr(void *para) {

	TIMERG0.hw_timer[TIMER_0].update = 1;
	TIMERG0.int_clr_timers.t0 = 1;

	/* After the alarm has been triggered
	 we need enable it again, so it is triggered the next time */
	TIMERG0.hw_timer[TIMER_0].config.alarm_en = TIMER_ALARM_EN;

	/* Now just send the event data back to the main program task */
	// ESP_LOGI(TAG, "ISR Done");
	gpio_set_level(LED, led_count % 2);
	led_count ++;
}




void IRAM_ATTR timer1_isr(void *para) {

	TIMERG0.hw_timer[TIMER_1].update = 1;
	TIMERG0.int_clr_timers.t1 = 1;

	/* After the alarm has been triggered
	 we need enable it again, so it is triggered the next time */
	TIMERG0.hw_timer[TIMER_1].config.alarm_en = TIMER_ALARM_EN;

	/* Now just send the event data back to the main program task */
	// ESP_LOGI(TAG, "ISR Done");

	struct controller_evt_t controller_data;


	pcnt_get_counter_value(PCNT_UNIT_0, &controller_data.count1);
	pcnt_get_counter_value(PCNT_UNIT_2, &controller_data.count2);

	timer_get_counter_value(TIMER_GROUP_0, TIMER_0, &controller_data.angle_timer);
	controller_data.t_count = timercount;
	timercount ++;

	xQueueSendToFrontFromISR(timer_queue, &controller_data, NULL);
}

void timer1_init() {
	/* Select and initialize basic parameters of the timer */
	timer_config_t config;
	config.divider = TIMER_DIVIDER;
	config.counter_dir = TIMER_COUNT_UP;
	config.counter_en = TIMER_PAUSE;
	config.alarm_en = TIMER_ALARM_EN;
	config.intr_type = TIMER_INTR_LEVEL;
	config.auto_reload = TIMER_AUTORELOAD_EN;
	timer_init(TIMER_GROUP_0, TIMER_1, &config);

	/* Timer's counter will initially start from value below.
	 Also, if auto_reload is set, this value will be automatically reload on alarm */
	timer_set_counter_value(TIMER_GROUP_0, TIMER_1, 0x00000000ULL);

	/* Configure the alarm value and the interrupt on alarm. */
	timer_set_alarm_value(TIMER_GROUP_0, TIMER_1,
			TIMER_INTERVAL1_SEC * TIMER_SCALE);
	timer_enable_intr(TIMER_GROUP_0, TIMER_1);
	timer_isr_register(TIMER_GROUP_0, TIMER_1, timer1_isr, (void *) TIMER_1,
			ESP_INTR_FLAG_IRAM, NULL);

	timer_start(TIMER_GROUP_0, TIMER_1);
}


void timer0_init() {
	/* Select and initialize basic parameters of the timer */
	timer_config_t config;
	config.divider = TIMER_DIVIDER;
	config.counter_dir = TIMER_COUNT_UP;
	config.counter_en = TIMER_PAUSE;
	config.alarm_en = TIMER_ALARM_EN;
	config.intr_type = TIMER_INTR_LEVEL;
	config.auto_reload = TIMER_AUTORELOAD_EN;
	timer_init(TIMER_GROUP_0, TIMER_0, &config);

	/* Timer's counter will initially start from value below.
	 Also, if auto_reload is set, this value will be automatically reload on alarm */
	timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0x00000000ULL);

	/* Configure the alarm value and the interrupt on alarm. */
	timer_set_alarm_value(TIMER_GROUP_0, TIMER_0,
			TIMER_INTERVAL0_SEC * TIMER_SCALE);
	timer_enable_intr(TIMER_GROUP_0, TIMER_0);
	timer_isr_register(TIMER_GROUP_0, TIMER_0, timer0_isr, (void *) TIMER_0,
			ESP_INTR_FLAG_IRAM, NULL);

	timer_start(TIMER_GROUP_0, TIMER_0);
}



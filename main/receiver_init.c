/*
 * receiver_init.c
 *
 *  Created on: 18.12.2018
 *      Author: malte
 */

#include "receiver_init.h"


void receiver_init(void){

	static const char* TAG = "receiver_init";

		// ONBOARD LED
		gpio_config_t io_conf;
		io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
		//set as output mode
		io_conf.mode = GPIO_MODE_OUTPUT;
		//bit mask of the pins that you want to set,e.g.GPIO18/19
		io_conf.pin_bit_mask = (1ULL << LED);
		//disable pull-down mode
		io_conf.pull_down_en = 0;
		//disable pull-up mode
		io_conf.pull_up_en = 0;
		//configure GPIO with the given settings
		gpio_config(&io_conf);

		//Install  Interupt on Laser_RX


		//interrupt of rising edge
		io_conf.intr_type = GPIO_PIN_INTR_POSEDGE;
		//bit mask of the pins, use GPIO4/5 here
		io_conf.mode = GPIO_MODE_INPUT;
		//disable pull-up/-down mode
		io_conf.pin_bit_mask = (1<<LASER_RX);
		//set as input mode
		io_conf.pull_up_en = 0;
		io_conf.pull_down_en = 0;

		gpio_config(&io_conf);

		gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
		//hook isr handler for specific gpio pin
		gpio_isr_handler_add(LASER_RX, rx_isr_handler, (void*) LASER_RX);


}

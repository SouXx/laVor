/*
 * receiver_init.c
 *
 *  Created on: 18.12.2018
 *      Author: malte
 */

#include "receiver_init.h"

static const char* TAG = "Receiver_Init";


void IRAM_ATTR rx_isr_handler(void* arg){

	uint64_t timer_value = 0;
	timer_get_counter_value(TIMER_GROUP_0, TIMER_0, &timer_value);
	xQueueSendFromISR(receiver_queue, &timer_value, NULL);



}




void receiver_init(void){

	static const char* TAG = "Receiver_Init";


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


		receiver_queue = xQueueCreate(10, sizeof(uint64_t));
		position_queue = xQueueCreate(100, sizeof(struct pos_t));


		//timer0_init();

		ESP_LOGI(TAG,"Init Done!");

}

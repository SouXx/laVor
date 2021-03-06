/*
 * pcnt.c
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

#include "pcnt.h"
static const char* TAG = "Pulse Counter";


void IRAM_ATTR index_isr_handler(void* arg) {

	//Counter bei Indexflanke zurücksetzen
	pcnt_counter_clear(PCNT_UNIT_0);
	pcnt_counter_clear(PCNT_UNIT_2);

	//printf("RESET \n");

}



void pcnt_init(void){
	//decoder phase A
		pcnt_config_t pcnt_config = {
		/*Set PHASE_A as pulse input gpio */
		.pulse_gpio_num = ENCODER_A,
		/*set PCNT_INPUT_CTRL_IO as control gpio (empty) */
		.ctrl_gpio_num = PCNT_PIN_NOT_USED,
		/*Choose channel 0 */
		.channel = PCNT_CHANNEL_0,
		/*Choose unit 0 */
		.unit = PCNT_UNIT_0,
		/*Set counter and control mode*/
		/*Counter increase for positive edge on pulse input GPIO*/
		.pos_mode = PCNT_COUNT_INC,
		/*Counter increase for negative edge on pulse input GPIO*/
		.neg_mode = PCNT_COUNT_INC,
		/*Counter mode keep as it is when control input is low level*/
		.lctrl_mode = PCNT_MODE_KEEP,
		//Counter mode does nothing when control input is high level*/
		.hctrl_mode = PCNT_MODE_KEEP,

		/*Set maximum value for increasing counter*/
		.counter_h_lim = PCNT_H_LIM_VAL,
		/*Set minimum value for decreasing counter*/
		.counter_l_lim = PCNT_L_LIM_VAL,
		};

	//Decoder phase B
		pcnt_config_t pcnt_config2 = {
		/*Set PHASE_B as pulse input gpio */
		.pulse_gpio_num = ENCODER_B,
		/*set PCNT_INPUT_CTRL_IO as control gpio(empty) */
		.ctrl_gpio_num = PCNT_PIN_NOT_USED,
		/*Choose channel 0 */
		.channel = PCNT_CHANNEL_0,
		/*Choose unit 2 */
		.unit = PCNT_UNIT_2,
		/*Set counter and control mode*/
		/*Counter increase for positive edge on pulse input GPIO*/
		.pos_mode = PCNT_COUNT_INC,
		/*Counter increase for negative edge on pulse input GPIO*/
		.neg_mode = PCNT_COUNT_INC,
		/*Counter mode keep as it is when control input is low level*/
		.lctrl_mode = PCNT_MODE_KEEP,
		/*Counter mode does nothing  when control input is high level*/
		.hctrl_mode = PCNT_MODE_KEEP,

		/*Set maximum value for increasing counter*/
		.counter_h_lim = PCNT_H_LIM_VAL,
		/*Set minimum value for decreasing counter*/
		.counter_l_lim = PCNT_L_LIM_VAL,
		};

		/*Initialize PCNT unit */
		if ((pcnt_unit_config(&pcnt_config) == ESP_OK)
			&& pcnt_unit_config(&pcnt_config2) == ESP_OK) {
			ESP_LOGI(TAG, "Pulse counter ready");
			pcnt_counter_pause(PCNT_UNIT_0);
			pcnt_counter_pause(PCNT_UNIT_2);
			pcnt_counter_clear(PCNT_UNIT_0);
			pcnt_counter_clear(PCNT_UNIT_2);
			pcnt_counter_resume(PCNT_UNIT_0);
			pcnt_counter_resume(PCNT_UNIT_2);

		}else{
			ESP_LOGI(TAG, "Pulse counter failed");
		}

		//Install ISR on Index to Reset Pulse counter

		gpio_config_t io_conf;

		//interrupt of rising edge
		io_conf.intr_type = GPIO_PIN_INTR_POSEDGE;
		//bit mask of the pins, use GPIO4/5 here
		io_conf.mode = GPIO_MODE_INPUT;
		//disable pull-up/-down mode
		io_conf.pin_bit_mask = (1<<ENCODER_I);
		//set as input mode
		io_conf.pull_up_en = 0;
		io_conf.pull_down_en = 0;

		gpio_config(&io_conf);

		gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
		//hook isr handler for specific gpio pin
		gpio_isr_handler_add(ENCODER_I, index_isr_handler, (void*) ENCODER_I);




}

/*
 * lavor_system.c
 * MOST OF THE CODE IS BASED ON EXAMPLES FROM hhtps://github.com/espresif/esp-idf
 *  Created on: Dec 20, 2018
 *      Author: tobias frahm
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
#include "lavor_system.h"

static const char *TAG = "[system] ";

void beacon_run(void *pvParameters) {
	esp_mqtt_event_handle_t event;
	unsigned int statrtup_flag = 0;
	ESP_LOGI(TAG, "Startup");
	beacon_salve_init();

	while(udpQueue != 0) {
		if (xQueueReceive(udpQueue, &udp_payload, (TickType_t) 10)) {
			char data_cmp[128] = "LAVOR_SYNC";

			ESP_LOGI(TAG, "%s", udp_payload.ucData);
			if (!strcmp(data_cmp, udp_payload.ucData) && !statrtup_flag) {
				timer0_init();

				// Only BEACON needs Timer 1!!
				timer1_init();
				ESP_LOGI(TAG, "timer started");
				//xTaskCreatePinnedToCore(beacon_controller,
				//"beacon_controller", 4096, NULL, 6, NULL, 0);
				//at receiver site this task must be the pos. calc task
				statrtup_flag = 1;
			}
		}
	}
	while (1) {
		//implement further logic here
		if (statrtup_flag) {
			if (mqttQueue != 0) {
				if (xQueueReceive(mqttQueue, &(event), (TickType_t) 10)) {
					ESP_LOGI(TAG, "mqtt_received");
					printf("DATA=%.*s\r\n", event->data_len, event->data);
					cjson_mc(event->data);
				}
			}
		}
		//esp_mqtt_client_publish(mqttClient, "/esp/test0", "test-esp", sizeof("test-esp"), 0, 0);
	}
}

void receiver_run(void *pvParameters) {
	receiver_init();
	uint64_t timer_value;
	int capture = 0;
	int capture_diff = 0;
	int last_capture = 0;

	while(udpQueue != 0) {
		if (xQueueReceive(udpQueue, &udp_payload, (TickType_t) 10)) {
			char data_cmp[128] = "LAVOR_SYNC";

			ESP_LOGI(TAG, "%s", udp_payload.ucData);
			if (!strcmp(data_cmp, udp_payload.ucData)) {
				timer0_init();

				// Only BEACON needs Timer 1!!
				ESP_LOGI(TAG, "timer started");
				//xTaskCreatePinnedToCore(beacon_controller,
				//"beacon_controller", 4096, NULL, 6, NULL, 0);
				//at receiver site this task must be the pos. calc task
				//statrtup_flag = 1;
			}
		}
	}

	while (1) {

		xQueueReceive(receiver_queue, &timer_value, portMAX_DELAY);
		capture = (int) timer_value;
		//printf("Capture: %d \n", capture);

		capture_diff = capture - last_capture;
		if (capture_diff < 0)
			capture_diff += 125000;

		if (capture_diff > LASER_INTR_DELAY) {

			receiver_calc(capture, last_capture);

			last_capture = capture;
		}
	}
}

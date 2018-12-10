/*
 * beacon.c
 *MOST CODE IS BASED ON EXAMPLES FROM https://github.com/espressif/esp-idf
 *  Created on: Nov 2, 2018
 *      Author: Tobias Frahm
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
#include "beacon.h"

static const char* TAG = "Beacon Control";
void beacon_slave_run(void *pvParameters) {
	//control
	ESP_LOGI(TAG, "Startup");
	beacon_salve_init();
	while (1) {

		vTaskDelay(500);
	}
}

void beacon_slave_test_run(void *pvParameters) {
	//control
	struct upd_event_t *udp_event;
	esp_mqtt_event_handle_t event;

	double time;
	ESP_LOGI(TAG, "Startup");
	beacon_salve_init();

	while (1) {

		if (udpQueue != 0) {
			if (xQueueReceive(udpQueue, &(udp_event), (TickType_t ) 10)) {
				ESP_LOGI(TAG, "udp_received");
				timer_pause(TIMER_GROUP_0, TIMER_0);
				timer_get_counter_time_sec(TIMER_GROUP_0, TIMER_0, &time);
				timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0x00000000ULL);
				timer_start(TIMER_GROUP_0, TIMER_0);
				ESP_LOGI(TAG, "Time[s] since last reset: %f", time);
			}
		}
		if (mqttQueue != 0) {
			if (xQueueReceive(mqttQueue, &(event), (TickType_t ) 10)) {
				ESP_LOGI(TAG, "mqtt_received");
				//printf("DATA=%.*s\r\n", event->data_len, event->data);
				cjson_mc(event->data);

			}
		}
		//vTaskDelay(2000);
		//esp_mqtt_client_publish(mqttClient, "/esp/test0", "test-esp", sizeof("test-esp"), 0, 0);
	}
}



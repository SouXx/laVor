/*
 * beacon.c
 *
 *  Created on: Nov 2, 2018
 *      Author: tobi
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
	ESP_LOGI(TAG, "Startup");
	beacon_salve_init();
	while (1) {
		if (udpQueue != 0) {
			if (xQueueReceive(udpQueue, &(udp_event), (TickType_t ) 10)) {
				ESP_LOGI(TAG, "udp_received");
				//post timer value
				//reset timer
				//start again
			}
		}
	}
}

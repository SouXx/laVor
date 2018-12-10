/*
 * beacon_init.c
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
#include "beacon_init.h"

void beacon_salve_init(void) {
	static const char* TAG = "beacon_slave";

	ESP_LOGI(TAG, "Initialize WIFI...");
	ESP_ERROR_CHECK(nvs_flash_init());
	initialise_wifi();
	wait_for_ip();
	ESP_LOGI(TAG, "done");
	ESP_LOGI(TAG, "Create UDP listener...");
	xTaskCreate(udp_server_task, "udp_client", 4096, NULL, 5, NULL);
	ESP_LOGI(TAG, "Initialize MCPWM module...");
	pwm_init();
	timer0_init();

	esp_log_level_set("*", ESP_LOG_INFO);
	esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
	esp_log_level_set("TRANSPORT_TCP", ESP_LOG_VERBOSE);
	esp_log_level_set("TRANSPORT_SSL", ESP_LOG_VERBOSE);
	esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
	esp_log_level_set("OUTBOX", ESP_LOG_VERBOSE);

	mqtt_app_start();
	vTaskDelay(500);
	ESP_LOGI(TAG, "done");
}

void beacon_master_init(void) {
	// so much space to fill
}

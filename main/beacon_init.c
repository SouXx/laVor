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
	xTaskCreatePinnedToCore(udp_server_task, "udp_server", 4096, NULL, 5, NULL,
			1);
	ESP_LOGI(TAG, "Initialize MCPWM module...");

	esp_log_level_set("*", ESP_LOG_INFO);
	esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
	esp_log_level_set("TRANSPORT_TCP", ESP_LOG_VERBOSE);
	esp_log_level_set("TRANSPORT_SSL", ESP_LOG_VERBOSE);
	esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
	esp_log_level_set("OUTBOX", ESP_LOG_VERBOSE);

	//mqtt_app_start();
	//beacon_controller_init();

	vTaskDelay(500);
	ESP_LOGI(TAG, "done");
}

void beacon_controller_init(void) {

	static const char* TAG = "beacon_controller";

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

	pwm_init();
	vTaskDelay(1000 / portTICK_PERIOD_MS);

	//gpio_init();
	pcnt_init();

	timer_queue = xQueueCreate(1, sizeof(struct controller_evt_t));
	if (mqttQueue == 0) {
		ESP_LOGI(TAG, "failed to create mqttQueue");
	}
	//timer0_init();
	timer1_init();
}

void broadcaster_init(void) {
	static const char* TAG = "[broadcaster]";

	ESP_LOGI(TAG, "Initialize WIFI...");
	ESP_ERROR_CHECK(nvs_flash_init());
	initialise_wifi();
	wait_for_ip();
	ESP_LOGI(TAG, "done");
	ESP_LOGI(TAG, "Create UDP socket...");
	xTaskCreatePinnedToCore(udp_client_task, "udp_client", 4096, NULL, 6, NULL,
					1);

}

void beacon_master_init(void) {
	// so much space to fill
}

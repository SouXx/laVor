/*
 * MOST CODE IS BASED ON EXAMPLES FROM https://github.com/espressif/esp-idf
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

#include "lavor_main.h"

static const char *TAG = "[lavor_main]";

void app_main() {

	/* Print chip information */
	esp_chip_info_t chip_info;

	esp_chip_info(&chip_info);
	ESP_LOGI(TAG, "This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
			chip_info.cores,
			(chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
			(chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
	ESP_LOGI(TAG, "silicon revision %d, ", chip_info.revision);

	ESP_LOGI(TAG, "%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
			(chip_info.features & CHIP_FEATURE_EMB_FLASH) ?
					"embedded" : "external");

#ifdef BEACON
	xTaskCreatePinnedToCore(beacon_run, "beacon_run", 4096, NULL, 5, NULL, 1);
	xTaskCreatePinnedToCore(beacon_controller, "beacon_controller", 4096, NULL, 6, NULL, 0);

#endif

#ifdef RECEIVER

	xTaskCreatePinnedToCore(receiver_run, "receiver_run", 4096, NULL, 6, NULL, 0);

#endif

#ifdef BROADCASTER

	xTaskCreatePinnedToCore(broadcaster, "broadcaster", 4096, NULL, 6, NULL,0);
#endif

	while (1) {
		vTaskSuspend(NULL);
	}
	vTaskDelete(NULL);

}

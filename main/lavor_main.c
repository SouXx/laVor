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

void app_main() {
	printf("Hello world!\n");

	/* Print chip information */
	esp_chip_info_t chip_info;

	esp_chip_info(&chip_info);
	printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ", chip_info.cores,
			(chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
			(chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
	printf("silicon revision %d, ", chip_info.revision);

	printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
			(chip_info.features & CHIP_FEATURE_EMB_FLASH) ?
					"embedded" : "external");

	xTaskCreate(beacon_slave_test_run, "beacon_slave_test_run", 4096, NULL, 5, NULL);
	xTaskCreate(beacon_controller, "beacon_controller", 4096, NULL, 6, NULL);

	while (1) {
		vTaskDelay(500);
	}
	vTaskDelete(NULL);

}

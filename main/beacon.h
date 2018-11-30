/*
 * beacon.h
 *MOST CODE IS BASED ON EXAMPLES FROM https://github.com/espressif/esp-idf
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

#ifndef MAIN_BEACON_H_
#define MAIN_BEACON_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "lavor_main.h"
#include "beacon_init.h"
#include "system_config.h"
#include "udp.h"
#include "timer.h"
#include "cJSON.h"

void beacon_slave_run(void *pvParameters);
void beacon_slave_test_run(void *pvParameters);

extern QueueHandle_t udpQueue;


#endif /* MAIN_BEACON_H_ */

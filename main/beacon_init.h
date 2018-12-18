/*
 * beacon_init.h
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

#ifndef MAIN_BEACON_INIT_H_
#define MAIN_BEACON_INIT_H_
//home/tobi/esp/esp-idf/components/driver/include/driver

#include "lavor_main.h"


#include "esp_err.h"


#include "wifi.h"
#include "mcpwm.h"
#include "udp.h"
#include "system_config.h"
#include "timer.h"
#include "mqtt.h"
#include "pcnt.h"


void beacon_salve_init(void);
void beacon_master_init(void);
void beacon_controller_init(void);
void broadcaster_init(void);

extern esp_mqtt_client_handle_t mqttClient;
#endif /* MAIN_BEACON_INIT_H_ */

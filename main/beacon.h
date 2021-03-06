/*
 * beacon.h
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

#ifndef MAIN_BEACON_H_
#define MAIN_BEACON_H_

#include "system_include.h"
#include "beacon_init.h"
#include "lavor_cJSON.h"
#include "udp.h"
#include "timer.h"

void beacon_slave_run(void *pvParameters);
void beacon_slave_test_run(void *pvParameters);
void beacon_controller(void *pvParameters);
void broadcaster(void  *pvParameters);


//struct udp_event_t udp_payload;

extern QueueHandle_t timer_queue;
extern QueueHandle_t udpQueue;
extern QueueHandle_t mqttQueue;
extern QueueHandle_t mcQueue;

#endif /* MAIN_BEACON_H_ */

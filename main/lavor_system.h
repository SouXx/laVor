/*
 * lavor_system.h
 * MOST OF THE CODE IS BASED ON EXAMPLES FROM hhtps://github.com/espresif/esp-idf
 *  Created on: Dec 20, 2018
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

#ifndef MAIN_LAVOR_SYSTEM_H_
#define MAIN_LAVOR_SYSTEM_H_


#include "system_include.h"
#include "beacon_init.h"
#include "receiver_init.h"
#include "lavor_cJSON.h"
#include "udp.h"
#include "timer.h"
#include "receiver.h"

extern QueueHandle_t timer_queue;
extern QueueHandle_t udpQueue;
extern QueueHandle_t mqttQueue;
extern QueueHandle_t mcQueue;
extern QueueHandle_t receiver_queue;

void beacon_run(void *pvParameters);
void receiver_run(void *pvParameters);
void broadcaster(void *pvParameters);

#endif /* MAIN_LAVOR_SYSTEM_H_ */

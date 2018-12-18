 /* receiver.h
 *
 *  Created on: 18.12.2018


 *      Author: malte
 *
 * this code is part of the LaVOR system application. Please see the license.txt
 * file for further information.
 *
 * The code is licensed under the
 *
 * 		Creative Commmons Attribution-NonCommercial-ShareAlike 4.0 International License.
 *
 * You are free to use this code for non-commercial applications as long as you leave this
 * attribution included in all copies or substantial portions of the Software.
 
 * Authors: Tobias Frahm, Philipp Haenyes, Joschka Sondhof, Josefine Palm, Malte Rejzek
 */

#ifndef MAIN_RECEIVER_H_
#define MAIN_RECEIVER_H_


#include "lavor_main.h"


#include "esp_err.h"


#include "wifi.h"
#include "mcpwm.h"
#include "udp.h"
#include "system_config.h"
#include "timer.h"
#include "mqtt.h"
#include "pcnt.h"
#include "receiver.h"

extern QueueHandle_t receiver_queue;


void receiver_run(void);

#endif /* MAIN_RECEIVER_H_ */

/*
 * udp.h
 *MOST CODE IS BASED ON EXAMPLES FROM https://github.com/espressif/esp-idf
 *  Created on: Nov 9, 2018
 *      Author: tobi
 */

#ifndef MAIN_UDP_H_
#define MAIN_UDP_H_

#include "system_include.h"


void udp_client_task(void *pvParameters);
void udp_server_task(void *pvParameters);

struct udp_event_t udp_payload;

QueueHandle_t udpQueue;

#endif /* MAIN_UDP_H_ */


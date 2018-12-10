/*
 * udp.h
 *MOST CODE IS BASED ON EXAMPLES FROM https://github.com/espressif/esp-idf
 *  Created on: Nov 9, 2018
 *      Author: tobi
 */

#ifndef MAIN_UDP_H_
#define MAIN_UDP_H_

#include <string.h>
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/err.h"
#include <lwip/netdb.h>
#include <sys/param.h>

#include "esp_log.h"
#include "freertos/queue.h"

#include "system_config.h"

void udp_client_task(void *pvParameters);
void udp_server_task(void *pvParameters);

struct udp_event_t {
	char ucData[128];
} udp_payload;

QueueHandle_t udpQueue;

#endif /* MAIN_UDP_H_ */


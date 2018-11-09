/*
 * udp.h
 *
 *  Created on: Nov 9, 2018
 *      Author: tobi
 */

#ifndef MAIN_UDP_H_
#define MAIN_UDP_H_

#include <string.h>
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>
#include "esp_log.h"

#include "system_config.h"

void udp_client_task(void *pvParameters);

#endif /* MAIN_UDP_H_ */

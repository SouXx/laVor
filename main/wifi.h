/*
 * wifi.h
 *
 *  Created on: Nov 3, 2018
 *      Author: tobi
 */

#ifndef MAIN_WIFI_H_
#define MAIN_WIFI_H_


#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "system_config.h"

void udp_start();
#endif /* MAIN_WIFI_H_ */

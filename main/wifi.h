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



#include "system_config.h"

void initialise_wifi(void);
void wait_for_ip();
esp_err_t event_handler(void *ctx, system_event_t *event);

#endif /* MAIN_WIFI_H_ */

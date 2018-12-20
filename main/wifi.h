/*
 * wifi.h
 *
 *  Created on: Nov 3, 2018
 *      Author: tobi
 */

#ifndef MAIN_WIFI_H_
#define MAIN_WIFI_H_




#include "system_include.h"

void initialise_wifi(void);
void wait_for_ip();
esp_err_t event_handler(void *ctx, system_event_t *event);

#endif /* MAIN_WIFI_H_ */

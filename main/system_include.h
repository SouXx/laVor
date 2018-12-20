/*
 * system_include.h
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
// #include "system_include.h"
#ifndef MAIN_SYSTEM_INCLUDE_H_
#define MAIN_SYSTEM_INCLUDE_H_

// udp

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stddef.h>


#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/portmacro.h"
#include "freertos/semphr.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/err.h"
#include <lwip/netdb.h>
#include "lwip/dns.h"

#include <sys/param.h>


#include "esp_intr_alloc.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_attr.h"
#include "esp_types.h"
#include "esp_spi_flash.h"
#include "esp_wifi.h"

#include "mqtt_client.h"

#include "driver/pcnt.h"
#include "driver/gpio.h"
#include "driver/periph_ctrl.h"
#include "driver/mcpwm.h"
#include "driver/timer.h"

#include "soc/gpio_sig_map.h"
#include "soc/timer_group_struct.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"
#include "soc/rtc.h"

#include "nvs_flash.h"



#include "system_config.h"

#endif /* MAIN_SYSTEM_INCLUDE_H_ */

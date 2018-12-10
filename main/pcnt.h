/*
 * pcnt.h
 *MOST CODE IS BASED ON EXAMPLES FROM https://github.com/espressif/esp-idf
 *  Created on: Nov 15, 2018
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

#ifndef MAIN_PCNT_H_
#define MAIN_PCNT_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/portmacro.h"
#include "driver/pcnt.h"
#include "driver/gpio.h"
#include "driver/periph_ctrl.h"
#include "soc/gpio_sig_map.h"
#include "esp_err.h"
#include "esp_attr.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_types.h"
#include "esp_spi_flash.h"
#include "system_config.h"





void pcnt_init(void);
void IRAM_ATTR index_isr_handler(void* arg);





#endif /* MAIN_PCNT_H_ */

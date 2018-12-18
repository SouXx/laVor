 /* receiver.c
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
 
 * Authors: Tobias Frahm, Philipp Haenyes, Joschka Sondhof, Josefine Palm, Malte Rejzek/*
 */


#include "receiver.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "lavor_main.h"
#include "beacon_init.h"
#include "lavor_cJSON.h"
#include "system_config.h"
#include "udp.h"
#include "timer.h"

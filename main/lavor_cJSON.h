/*
 * cJSON.h
 * MOST OF THE CODE IS BASED ON EXAMPLES FROM hhtps://github.com/espresif/esp-idf
 *  Created on: Dec 1, 2018
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

#ifndef MAIN_LAVOR_CJSON_H_
#define MAIN_LAVOR_CJSON_H_

#include "cJSON.h"
#include "lavor_main.h"
#include "freertos/queue.h"
#include "system_config.h"

QueueHandle_t mcQueue;
int cjson_mc(const char * const data);


#endif /* MAIN_LAVOR_CJSON_H_ */

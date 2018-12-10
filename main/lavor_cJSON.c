/*
 * cJSON.c
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

#include "lavor_cJSON.h"

const char *TAG = "cJSON";

int cjson_mc(const char * const data) {
	motor_control_values_t	newMCValues;

	mcQueue = xQueueCreate(10, sizeof(struct motor_control_values_t*));
		if( mcQueue == 0 )
		    {
			ESP_LOGI(TAG, "failed to create mcQueue");
		    }

	const cJSON *con_speed_setpoint = NULL;
	const cJSON *con_i = NULL;
	const cJSON *con_p = NULL;
	const cJSON *con_d = NULL;
	const cJSON *con_a = NULL;

	int status = 0;
	cJSON *data_json = cJSON_Parse(data);

	if (data_json == NULL) {
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL) {
			fprintf(stderr, "Error before: %s\n", error_ptr);
		}
		status = 0;
		goto end;
	}

	con_speed_setpoint = cJSON_GetObjectItemCaseSensitive(data_json,
			"con_speed_setpoint");
	if (cJSON_IsString(con_speed_setpoint)
			&& (con_speed_setpoint->valuestring != NULL)) {
		newMCValues.con_speed_setpoint = atof(con_speed_setpoint->valuestring);
		printf("con_speed_setpoint \"%s\"\n", con_speed_setpoint->valuestring);
	}
	con_p = cJSON_GetObjectItemCaseSensitive(data_json,
			"con_p");
	if (cJSON_IsString(con_p) && (con_p->valuestring != NULL)) {
		newMCValues.con_p = atof(con_p->valuestring);
		printf("con_p \"%s\"\n", con_p->valuestring);
	}

	con_i = cJSON_GetObjectItemCaseSensitive(data_json, "con_i");
	if (cJSON_IsString(con_i) && (con_i->valuestring != NULL)) {
		newMCValues.con_i = atof(con_i->valuestring);
		printf("con_i \"%s\"\n", con_i->valuestring);
	}
	con_d = cJSON_GetObjectItemCaseSensitive(data_json, "con_p");
	if (cJSON_IsString(con_d) && (con_d->valuestring != NULL)) {
		newMCValues.con_d = atof(con_d->valuestring);
		printf("con_d \"%s\"\n", con_d->valuestring);
	}
	con_a = cJSON_GetObjectItemCaseSensitive(data_json, "con_p");
		if (cJSON_IsString(con_a) && (con_a->valuestring != NULL)) {
			newMCValues.con_a = atof(con_a->valuestring);
			printf("con_a \"%s\"\n", con_a->valuestring);
		}
	//Queue
	if (xQueueSend(mcQueue, (void * ) &newMCValues,
			(TickType_t ) 10) != pdPASS) {
		ESP_LOGI(TAG, "Queue push failed");
	}

	end: cJSON_Delete(data_json);
	return status;

}

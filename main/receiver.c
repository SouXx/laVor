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
 
 * Authors: Tobias Frahm, Philipp Haenyes, Joschka Sondhof, Josefine Palm, Malte Rejzek
 */

#include "receiver.h"

void receiver_pos_task(void) {

	static const char* TAG = "[mean_position]";

	int pos_counter = 0;
	int meanX = 0;
	int meanY = 0;
	struct pos_t rx_pos;

//	msg.payload = {
//	  tstamp: 1438637044000,
//	  data: {
//	    x: 3.14,
//	    y: 1.41
//	  }
//	}
	cJSON *tstamp = NULL;
	cJSON *x = NULL;
	cJSON *y = NULL;

	cJSON *pos = cJSON_CreateObject();
	cJSON *data = cJSON_CreateObject();

	while (1) {
		//int cnt = position_queue;

		//ESP_LOGI(TAG, "Queue: %d", cnt);

		while (uxQueueMessagesWaiting(position_queue)) {

			xQueueReceive(position_queue, &rx_pos, portMAX_DELAY);
			meanX += rx_pos.posX;
			meanY += rx_pos.posY;
			pos_counter++;

			/*	if (pos_counter >= cnt) {
			 meanX /= pos_counter;
			 meanY /= pos_counter;
			 x = cJSON_CreateNumber(meanX);
			 y = cJSON_CreateNumber(meanY);

			 ESP_LOGI(TAG, "Mean Position X: %d \t Y: %d", meanX, meanY);
			 meanX = 0;
			 meanY = 0;
			 pos_counter = 0;
			 }*/
		}

		meanX /= pos_counter;
		meanY /= pos_counter;
		x = cJSON_CreateNumber(meanX);
		y = cJSON_CreateNumber(meanY);

		ESP_LOGI(TAG, "Mean Position X: %d \t Y: %d", meanX, meanY);
		meanX = 0;
		meanY = 0;
		pos_counter = 0;

		cJSON_AddItemToObject(data, "x", x);
		cJSON_AddItemToObject(data, "y", y);
		cJSON_AddItemToObject(pos, "tstamp", tstamp);
		cJSON_AddItemToObject(pos, "data", data);

		esp_mqtt_client_publish(mqttClient, "/esp/pos", pos, sizeof(pos), 0, 0);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}

void receiver_calc(int cap_1, int cap_2) {

	static const char* TAG = "[receiver_calculation]";

	struct pos_t calc_pos;

	//Capture sort to order by size
	int cap1 = 0;
	int cap2 = 0;

	if (cap_1 > cap_2) {
		cap1 = cap_2;
		cap2 = cap_1;
	} else {
		cap1 = cap_1;
		cap2 = cap_2;
	}

	printf("Capture: %d \t %d \n", cap1, cap2);

	float xp = -1;
	float yp = -1;

	float m1 = 1.0 / tan((float) cap1 * 5.0265e-5);
	float m2 = 1.0 / tan((float) cap2 * 5.0265e-5);

	//printf("M1: %f M2: %f \n", m1, m2);

	// Beacon 1 and Beacon 2
	if (cap1 >= 0 && cap1 < 31250 && cap2 >= 31250 && cap2 < 62500) {
		xp = (BEACON_2_Y) / (m1 - m2);
		yp = m1 * xp;

		ESP_LOGI(TAG, "1 and 2 --> X: %f \t Y: %f", xp, yp);
		xQueueSend(position_queue, &calc_pos, NULL);

	}
	// Beacon 2 and Beacon 3( vlt nicht sinnvoll?!?
	else if (0 && cap1 >= 31250 && cap1 < 62500 && cap2 >= 93750
			&& cap2 < 125000) {
		xp = ((-m2 * BEACON_3_X) - BEACON_2_Y) / (m1 - m2);
		yp = (m1 * xp) + BEACON_2_Y;

		ESP_LOGI(TAG, "2 and 3 --> X: %f \t Y: %f", xp, yp);
		xQueueSend(position_queue, &calc_pos, NULL);

	}
	//Beacon 1 and Beacon 3
	else if (cap1 >= 0 && cap1 < 31250 && cap2 >= 93750 && cap2 < 125000) {
		xp = (-m2 * BEACON_3_X) / (m1 - m2);
		yp = m1 * xp;

		ESP_LOGI(TAG, "1 and 3 --> X: %f \t Y: %f", xp, yp);
		xQueueSend(position_queue, &calc_pos, NULL);

	}
	// Values out of Range
	else {
		ESP_LOGW(TAG, "Values out of Range!");
	}

}


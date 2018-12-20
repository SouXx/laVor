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

void receiver_calc(int cap1, int cap2) {

	static const char* TAG = "Receiver calculation";

	//Capture sort to order by size
	if (cap1 > cap2) {
		int temp = cap1;
		int cap1 = cap2;
		int cap2 = cap1;
	}

	float xp = -1.0;
	float yp = -1.0;

	float m1 = 1.0 / tan((float) cap1 * 5.0265e-5);
	float m2 = 1.0 / tan((float) cap1 * 5.0265e-5);

	// Beacon 1 and Beacon 2
	if (cap1 >= 0 && cap1 < 31250 && cap2 >= 31250 && cap2 < 62500) {
		xp = (BEACON_2_Y) / (m1 - m2);
		yp = m1 * xp;

	}
	// Beacon 2 and Beacon 3
	else if (cap1 >= 31250 && cap1 < 62500 && cap2 >= 93750 && cap2 < 125000) {
		xp = ((-m2 * BEACON_3_X) - BEACON_2_Y) / (m1 - m2);
		yp = (m1 * xp) + BEACON_2_Y;
	}
	//Beacon 1 and Beacon 3
	else if (cap1 >= 0 && cap1 < 31250 && cap2 >= 93750 && cap2 < 125000 ) {
		xp = (-m2 * BEACON_3_X) / (m1 - m2);
		yp = m1 * xp;
	}
	// Values out of Range
	else {
		ESP_LOGW(TAG, "Values out of Range!");
	}

	printf("Position: X= %f  Y= %f",xp,yp);

}

void receiver_run(void) {

	receiver_init();
	uint64_t timer_value;
	int capture = 0;
	int capture_diff = 0;
	int last_capture = 0;

	uint32_t captureBuffer[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	uint8_t captureBufferPos = 0;
	int pos[2];

	while (1) {
		xQueueReceive(receiver_queue, &timer_value, portMAX_DELAY);
		capture = (int) timer_value;
		printf("Capture: %d \n", capture);

		receiver_calc(15625,102960);

	}

}


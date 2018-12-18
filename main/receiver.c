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

void receiver_run(void){

	receiver_init();
	uint64_t timer_value;
	int capture = 0;
	int capture_diff = 0;
	int last_capture = 0;

	uint32_t captureBuffer[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint8_t captureBufferPos = 0;
	int pos[2];

	while(1){
		xQueueReceive(receiver_queue, &timer_value, portMAX_DELAY);
		capture = (int)timer_value;
		printf("Capture: %d \n", capture);

		capture_diff = capture - last_capture;
		if (capture_diff < 0) capture_diff += 125000;

		if (capture_diff > INTR_DELAY) {
		    captureBuffer[captureBufferPos] = capture_diff;
		    last_capture = capture;
		    captureBufferPos ++;
		    if (captureBufferPos > 9) {
		      captureBufferPos = 9;
		    }
		  }


	}

}


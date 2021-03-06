/*
 * beacon.c
 *MOST CODE IS BASED ON EXAMPLES FROM https://github.com/espressif/esp-idf
 *  Created on: Nov 2, 2018
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
#include "beacon.h"

static const char* TAG = "Beacon Control";

void beacon_controller(void *pvParameters) {

	static const char* TAG = "[beacon_controller]";

	//control
	beacon_controller_init();

	motor_control_values_t newMCValues;
	// Berechnet die Schrittweite für Lageregler
	//	        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM0A, MCPWM_OPR_A, y); // "Anschubsen"
	//	    	vTaskDelay(100/portTICK_PERIOD_MS);

	// Werte für Regler, update später über MQTT!
	int s_setpoint = (int) (ENCODER_CPR * CON_SPEED_SETPOINT / CON_FREQUENCY); //		1600*8/80 = 160
	float p = CON_P;
	float i = CON_I;
	float d = CON_D;
	float a = CON_A;

	int angle_factor = (1000000.0 / (CON_SPEED_SETPOINT * ENCODER_CPR));
	int a_setpoint = 0;

	int s_e_sum = 0;
	int s_e_old = 0;
	float y = 20.0;
	int speed = 0;
	// Ziele für Queues
	// uint32_t capture = 0;
	int count = 0;
	int old_count = 0;
	int limit_setpoint = 0;
	//mcpwm_set_duty(MCPWM_UNIT_0, MCPWM0A, MCPWM_OPR_A, y); // "Anschubsen"
	//vTaskDelay(100/portTICK_PERIOD_MS);

	struct controller_evt_t controller_data;

	while (1) {

		xQueueReceive(timer_queue, &controller_data, portMAX_DELAY);
		// Capture erstmal außer Betrieb...
		//xQueueReceive(cap_queue, &capture, 0);
		//if(capture > 0 ) speed = (4000000000 / capture) * 2; //Speed in mHz

		count = controller_data.count1 + controller_data.count2;
		speed = count - old_count;
		if (speed < 0)
			speed += ENCODER_CPR;
		if (speed > 200)
			speed = s_setpoint;

		a_setpoint = controller_data.angle_timer / angle_factor;
		int a_e = a_setpoint - count;
		if (a_e > 800)
			a_e -= 1600;
		if (a_e <= -800)
			a_e += 1600;

		if (limit_setpoint < s_setpoint) {
			limit_setpoint++;
			a_e = 0;
		}

		int s_e = (limit_setpoint) - speed + (int) (a_e * a); // Regelfehler berechnen
		if (y < 100.0)
			s_e_sum += s_e; //Integrierer Begrenzt wenn Limit der Stellgröße erreicht(ANTI-WINDUP)
		y = (p * (float) s_e) + (i / CON_FREQUENCY * (float) s_e_sum)
				+ d * CON_FREQUENCY * (float) (s_e - s_e_old);

		// Begrenzung für Duty-Cycle
		if (y >= 100.0)
			y = 100.0;
		if (y < 0.0)
			y = 0.0;

		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM0A, MCPWM_OPR_A, y);

		//ESP_LOGI(TAG, "Angle error: %d \n", a_e);

		s_e_old = s_e;
		old_count = count;

	}

}


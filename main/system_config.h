/*
 * system_config.h
 *
 *  Created on: Nov 2, 2018
 *      Author: tobi
 */

#ifndef MAIN_SYSTEM_CONFIG_H_
#define MAIN_SYSTEM_CONFIG_H_


// MOTOR/MCPWM CONFIG
#define MOTOR_SLEEP_OUT_PIN 			(22)
#define MOTOR_DIR_OUT_PIN 				(18)
#define MOTOR_PWM_OUT_PIN 				(32)
#define PUBLISH_FREQUENCY				(750) /* Hz */
#define CAPTURE_RISING					(1)

//WIFI
#define CONFIG_WIFI_SSID			"sRx"
#define CONFIG_WIFI_PASSWORD		"7uzgl4TF"
#define CONFIG_ESP_MAXIMUM_RETRY		(5)
#define CONFIG_EXAMPLE_IPV4_ADDR	"89.15.239.250"
#define CONFIG_EXAMPLE_IPV4			true
#define CONFIG_EXAMPLE_PORT			(80)
#endif /* MAIN_SYSTEM_CONFIG_H_ */

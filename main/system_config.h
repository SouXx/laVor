/*
 * system_config.h
 *
 *  Created on: Nov 2, 2018
 *      Author: tobi
 */
#ifndef MAIN_SYSTEM_CONFIG_H_
#define MAIN_SYSTEM_CONFIG_H_

//#define CONFIG_LOG_DEFAULT_LEVEL          ESP_LOG_INFO

//ONBAORD CONFIG
#define LED 							(2)
#define BUTTON							(0)

// CONTROLLER CONFIG
#define CON_SPEED_SETPOINT				(10) // Revolutions per second
#define CON_FREQUENCY					(100)// Must be multiple of speed setpoint
#define CON_P							(0)
#define CON_I							(0)

// MOTOR/MCPWM CONFIG
#define MOTOR_PWM_OUT_PIN 				(32)
#define PWM_FREQUENCY					(750) /* Hz */
#define CAPTURE_RISING					(1)
#define MCPWM_SELECT_CAP_PIN			(27)

// TIMER CONFIG
#define TIMER_DIVIDER         16  //  Hardware timer clock divider
#define TIMER_SCALE           (TIMER_BASE_CLK / TIMER_DIVIDER)  // convert counter value to seconds
#define TIMER_INTERVAL_SEC   (1.0 / CON_FREQUENCY)

// ENCODER CONFIG
#define ENCODER_CPR						(1600)
#define ENCODER_A						(4)
#define ENCODER_B						(27)
#define ENCODER_I						(15)
// PCNT CONFIG
#define PCNT_H_LIM_VAL					(3000)
#define PCNT_L_LIM_VAL					(0)
//WIFI
//#define CONFIG_WIFI_SSID			"WILHELM.TEL-1XL2CL11"
//#define CONFIG_WIFI_PASSWORD		"99545866246329488456"
#define CONFIG_WIFI_SSID			"lavor_sys0_master"
#define CONFIG_WIFI_PASSWORD		"7Q5JUgtJbVpJy2PYS4xF"

#define CONFIG_ESP_MAXIMUM_RETRY		(5)
#define HOST_IP_ADDR	"192.168.178.165"
#define PORT			(80)
#endif /* MAIN_SYSTEM_CONFIG_H_ */

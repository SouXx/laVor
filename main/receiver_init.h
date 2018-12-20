/*
 * receiver_init.h
 *
 *  Created on: 18.12.2018
 *      Author: malte
 */

#ifndef MAIN_RECEIVER_INIT_H_
#define MAIN_RECEIVER_INIT_H_


#include "system_include.h"

#include "lavor_main.h"
#include "wifi.h"
#include "mcpwm.h"
#include "udp.h"
#include "system_config.h"
#include "timer.h"
#include "mqtt.h"
#include "pcnt.h"
#include "receiver.h"

QueueHandle_t receiver_queue;
QueueHandle_t position_queue;

struct pos_t {
	int posX;
	int posY;
};



void receiver_init(void);
void IRAM_ATTR rx_isr_handler(void* arg);
#endif /* MAIN_RECEIVER_INIT_H_ */

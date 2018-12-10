/*
 * mqtt.c
 * MOST CODE IS BASED ON EXAMPLES FROM https://github.com/espressif/esp-idf
 *  Created on: Nov 16, 2018
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

#include "mqtt.h"

static const char *TAG = "MQTT_CLIENT";

esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event) {
	esp_mqtt_client_handle_t client = event->client;

	mqttQueue = xQueueCreate(10, sizeof(struct esp_mqtt_client_handle_t*));
	if( mqttQueue == 0 )
	    {
		ESP_LOGI(TAG, "failed to create mqttQueue");
	    }

	int msg_id;
	//motor_control_values_t *context = event->user_context;

	switch (event->event_id) {
	case MQTT_EVENT_CONNECTED:
		ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
		//msg_id = esp_mqtt_client_subscribe(mqttClient, "/esp/test0", 0);
		//ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
		msg_id = esp_mqtt_client_publish(client, "/topic/qos1", "data_3", 0, 1,
				0);
		ESP_LOGI(TAG, "[MQTT_EVENT_CONNECTED]sent publish successful, msg_id=%d", msg_id);

		msg_id = esp_mqtt_client_subscribe(client, "/esp/test0", 0);
		ESP_LOGI(TAG, "[MQTT_EVENT_CONNECTED]sent subscribe successful, msg_id=%d", msg_id);

		msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
		ESP_LOGI(TAG, "[MQTT_EVENT_CONNECTED]sent subscribe successful, msg_id=%d", msg_id);

		msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
		ESP_LOGI(TAG, "[MQTT_EVENT_CONNECTED]sent unsubscribe successful, msg_id=%d", msg_id);
		break;
	case MQTT_EVENT_DISCONNECTED:
		ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
		break;

	case MQTT_EVENT_SUBSCRIBED:
		ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
		msg_id = esp_mqtt_client_publish(client, "/esp/test0", "data", 0, 0,
				0);
		ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
		break;
	case MQTT_EVENT_UNSUBSCRIBED:
		ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
		break;
	case MQTT_EVENT_PUBLISHED:
		ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
		break;
	case MQTT_EVENT_DATA:
		ESP_LOGI(TAG, "MQTT_EVENT_DATA");
		printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
		//printf("DATA=%.*s\r\n", event->data_len, event->data);
		if (xQueueSend(mqttQueue, (void * ) &event,
				(TickType_t ) 10) != pdPASS) {
			ESP_LOGI(TAG, "Queue push failed");
		}
		break;
	case MQTT_EVENT_ERROR:
		ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
		break;
	}
	return ESP_OK;
}

void mqtt_app_start(void) {

	motor_control_values_t mcv;

	mcv.con_speed_setpoint = CON_SPEED_SETPOINT;
	mcv.con_frequency = CON_FREQUENCY;
	mcv.con_i = CON_P;
	mcv.con_p = CON_I;

	esp_mqtt_client_config_t mqtt_cfg = { .uri = CONFIG_BROKER_URL,
			.event_handle = mqtt_event_handler, .user_context = (void *) &mcv, };

#if CONFIG_BROKER_URL_FROM_STDIN
	char line[128];

	if (strcmp(mqtt_cfg.uri, "FROM_STDIN") == 0) {
		int count = 0;
		printf("Please enter url of mqtt broker\n");
		while (count < 128) {
			int c = fgetc(stdin);
			if (c == '\n') {
				line[count] = '\0';
				break;
			} else if (c > 0 && c < 127) {
				line[count] = c;
				++count;
			}
			vTaskDelay(10 / portTICK_PERIOD_MS);
		}
		mqtt_cfg.uri = line;
		printf("Broker url: %s\n", line);
	} else {
		ESP_LOGE(TAG, "Configuration mismatch: wrong broker url");
		abort();
	}
#endif /* CONFIG_BROKER_URL_FROM_STDIN */

	mqttClient = esp_mqtt_client_init(&mqtt_cfg);
	esp_mqtt_client_start(mqttClient);
}


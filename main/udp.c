/*
 * udp.c
 *MOST CODE IS BASED ON EXAMPLES FROM https://github.com/espressif/esp-idf
 *  Created on: Nov 9, 2018
 *      Author: tobi
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

#include "udp.h"

static const char *TAG = "UDP";
static const char *payload = "LAVOR_SYNC";

void udp_server_task(void *pvParameters) {
	char rx_buffer[128];
	char addr_str[128];
	int addr_family;
	int ip_protocol;

	struct upd_event_t *udp_event;
	udpQueue = xQueueCreate(10, sizeof(struct udp_event_t*));
	if( udpQueue == 0 )
	    {
		ESP_LOGI(TAG, "failed to create udpQueue");
	    }
	while (1) {

		struct sockaddr_in destAddr;
		destAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		destAddr.sin_family = AF_INET;
		destAddr.sin_port = htons(PORT);
		addr_family = AF_INET;
		ip_protocol = IPPROTO_IP;
		inet_ntoa_r(destAddr.sin_addr, addr_str, sizeof(addr_str) - 1);

		int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
		if (sock < 0) {
			ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
			break;
		}
		ESP_LOGI(TAG, "Socket created");

		int err = bind(sock, (struct sockaddr *) &destAddr, sizeof(destAddr));
		if (err < 0) {
			ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
		}
		ESP_LOGI(TAG, "Socket binded");

		while (1) {

			ESP_LOGI(TAG, "Waiting for data");
			struct sockaddr_in6 sourceAddr; // Large enough for both IPv4 or IPv6
			socklen_t socklen = sizeof(sourceAddr);
			int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0,
					(struct sockaddr *) &sourceAddr, &socklen);

			// Error occured during receiving
			if (len < 0) {
				ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
				break;
			}
			// Data received
			else {
				// Get the sender's ip address as string
				if (sourceAddr.sin6_family == PF_INET) {
					inet_ntoa_r(
							((struct sockaddr_in *) &sourceAddr)->sin_addr.s_addr,
							addr_str, sizeof(addr_str) - 1);
				} else if (sourceAddr.sin6_family == PF_INET6) {
					inet6_ntoa_r(sourceAddr.sin6_addr, addr_str,
							sizeof(addr_str) - 1);
				}

				rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string...
				ESP_LOGI(TAG, "Received %d bytes from %s:", len, addr_str);
				ESP_LOGI(TAG, "%s", rx_buffer);
				strcpy(udp_payload.ucData, rx_buffer);

				//udp_event = &udp_payload;
				if (xQueueSend(udpQueue, &udp_payload,
						(TickType_t ) 10) != pdPASS) {
					ESP_LOGI(TAG, "Queue push failed");
				}
				int err = sendto(sock, rx_buffer, len, 0,
						(struct sockaddr *) &sourceAddr, sizeof(sourceAddr));
				if (err < 0) {
					ESP_LOGE(TAG, "Error occured during sending: errno %d",
							errno);
					break;
				}
			}
		}

		if (sock != -1) {
			ESP_LOGE(TAG, "Shutting down socket and restarting...");
			shutdown(sock, 0);
			close(sock);
		}
	}
	vTaskDelete(NULL);
}

void udp_client_task(void *pvParameters) {
	char rx_buffer[128];
	char addr_str[128];
	int addr_family;
	int ip_protocol;

	while (1) {

		struct sockaddr_in destAddr;
		destAddr.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
		destAddr.sin_family = AF_INET;
		destAddr.sin_port = htons(PORT);
		addr_family = AF_INET;
		ip_protocol = IPPROTO_IP;
		inet_ntoa_r(destAddr.sin_addr, addr_str, sizeof(addr_str) - 1);

		int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
		if (sock < 0) {
			ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
			break;
		}
		ESP_LOGI(TAG, "Socket created");

		while (1) {

			int err = sendto(sock, payload, strlen(payload), 0,
					(struct sockaddr *) &destAddr, sizeof(destAddr));
			if (err < 0) {
				ESP_LOGE(TAG, "Error occured during sending: errno %d", errno);
				break;
			}
			ESP_LOGI(TAG, "Message sent");

			struct sockaddr_in sourceAddr; // Large enough for both IPv4 or IPv6
			socklen_t socklen = sizeof(sourceAddr);
			int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0,
					(struct sockaddr *) &sourceAddr, &socklen);

			// Error occured during receiving
			if (len < 0) {
				ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
				break;
			}
			// Data received
			else {
				rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
				ESP_LOGI(TAG, "Received %d bytes from %s:", len, addr_str);
				ESP_LOGI(TAG, "%s", rx_buffer);
			}

			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}

		if (sock != -1) {
			ESP_LOGE(TAG, "Shutting down socket and restarting...");
			shutdown(sock, 0);
			close(sock);
		}
	}
	vTaskDelete(NULL);
}

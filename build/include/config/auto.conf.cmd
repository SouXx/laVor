deps_config := \
	/home/tobi/esp/esp-idf/components/app_trace/Kconfig \
	/home/tobi/esp/esp-idf/components/aws_iot/Kconfig \
	/home/tobi/esp/esp-idf/components/bt/Kconfig \
	/home/tobi/esp/esp-idf/components/driver/Kconfig \
	/home/tobi/esp/esp-idf/components/esp32/Kconfig \
	/home/tobi/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/tobi/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/tobi/esp/esp-idf/components/ethernet/Kconfig \
	/home/tobi/esp/esp-idf/components/fatfs/Kconfig \
	/home/tobi/esp/esp-idf/components/freemodbus/Kconfig \
	/home/tobi/esp/esp-idf/components/freertos/Kconfig \
	/home/tobi/esp/esp-idf/components/heap/Kconfig \
	/home/tobi/esp/esp-idf/components/http_server/Kconfig \
	/home/tobi/esp/esp-idf/components/libsodium/Kconfig \
	/home/tobi/esp/esp-idf/components/log/Kconfig \
	/home/tobi/esp/esp-idf/components/lwip/Kconfig \
	/home/tobi/esp/esp-idf/components/mbedtls/Kconfig \
	/home/tobi/esp/esp-idf/components/mdns/Kconfig \
	/home/tobi/esp/esp-idf/components/mqtt/Kconfig \
	/home/tobi/esp/esp-idf/components/nvs_flash/Kconfig \
	/home/tobi/esp/esp-idf/components/openssl/Kconfig \
	/home/tobi/esp/esp-idf/components/pthread/Kconfig \
	/home/tobi/esp/esp-idf/components/spi_flash/Kconfig \
	/home/tobi/esp/esp-idf/components/spiffs/Kconfig \
	/home/tobi/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/tobi/esp/esp-idf/components/vfs/Kconfig \
	/home/tobi/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/tobi/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/tobi/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/tobi/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/tobi/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;

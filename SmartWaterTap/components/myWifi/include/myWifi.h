#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1

//test pentru Miele
//#define CONFIG_ESP_WIFI_SSID "XKM_TEST_NETWORK"
//#define CONFIG_ESP_WIFI_PASSWORD "iamnotallowedhere"

//test Miele depozit
//#define CONFIG_ESP_WIFI_SSID "EdiSon"
//#define CONFIG_ESP_WIFI_PASSWORD "Miele@WIFI"

//prezentare Miele
#define CONFIG_ESP_WIFI_SSID "Mihaidono"
#define CONFIG_ESP_WIFI_PASSWORD "Mihai1234"

class myWifi
{
private:
    static void event_handler(void *, esp_event_base_t, int32_t, void *);
    bool isConnected;

public:
    myWifi() {}
    ~myWifi();

    void wifi_init_sta(void);
    bool isWifiConnected();
};
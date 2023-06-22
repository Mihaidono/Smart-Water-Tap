#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_log.h"

class myNvs
{
private:
    nvs_handle storage_handle;

public:
    myNvs() {}

    esp_err_t init_myNvs();
    esp_err_t store_state(const char *);
    char *get_stored_state();

    esp_err_t store_wifi_credentials(const char *, const char *);
    char * get_stored_wifi_ssid();
    char * get_stored_wifi_password();

    void my_nvs_cleanup();
};
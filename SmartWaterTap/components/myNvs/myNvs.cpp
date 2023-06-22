#include "myNvs.h"

#define STORAGE_NAMESPACE "nvs_storage"
static const char *TAG = "NVS-Storage";

esp_err_t myNvs::init_myNvs()
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    if (err != ESP_OK)
    {
        return err;
    }
    err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &storage_handle);
    return err;
}

esp_err_t myNvs::store_state(const char *state)
{
    esp_err_t err = nvs_set_str(this->storage_handle, "tap_state", state);
    if (err != ESP_OK)
    {
        return err;
    }
    err = nvs_commit(storage_handle);
    ESP_LOGI(TAG, "SUCCESS STORING THE STATE");
    return err;
}

char *myNvs::get_stored_state()
{
    size_t required_size;
    char *tap_state;
    esp_err_t err = nvs_get_str(this->storage_handle, "tap_state", NULL, &required_size);
    if (err == ESP_OK)
    {
        tap_state = (char *)malloc(required_size);
        err = nvs_get_str(this->storage_handle, "tap_state", tap_state, &required_size);
        if (err == ESP_OK)
        {
            ESP_LOGI(TAG, "SUCCESS READING THE STATE");
            return tap_state;
        }
    }
    ESP_LOGI(TAG, "FAILED READING THE STATE");
    tap_state = nullptr;
    return tap_state;
}

esp_err_t myNvs::store_wifi_credentials(const char *ssid, const char *passwd)
{
    esp_err_t err = nvs_set_str(this->storage_handle, "wifi_ssid", ssid);
    if (err != ESP_OK)
    {
        ESP_LOGI(TAG, "FAILED STORING THE WIFI SSID");
        return err;
    }
    err = nvs_commit(storage_handle);

    err = nvs_set_str(this->storage_handle, "wifi_password", passwd);
    if (err != ESP_OK)
    {
        ESP_LOGI(TAG, "FAILED STORING THE WIFI PASSWORD");
        return err;
    }
    err = nvs_commit(storage_handle);
    ESP_LOGI(TAG, "SUCCESS STORING THE WIFI CREDENTIALS");
    return err;
}

char *myNvs::get_stored_wifi_ssid()
{
    size_t required_size;
    char *ssid;
    esp_err_t err = nvs_get_str(this->storage_handle, "wifi_ssid", NULL, &required_size);
    if (err == ESP_OK)
    {
        ssid = (char *)malloc(required_size);
        err = nvs_get_str(this->storage_handle, "wifi_ssid", ssid, &required_size);
        if (err == ESP_OK)
        {
            ESP_LOGI(TAG, "SUCCESS READING THE WIFI SSID");
            return ssid;
        }
    }
    ESP_LOGI(TAG, "FAILED READING THE WIFI SSID");
    ssid = nullptr;
    return ssid;
}

char *myNvs::get_stored_wifi_password()
{
    size_t required_size;
    char *passwd;
    esp_err_t err = nvs_get_str(this->storage_handle, "wifi_password", NULL, &required_size);
    if (err == ESP_OK)
    {
        passwd = (char *)malloc(required_size);
        err = nvs_get_str(this->storage_handle, "wifi_password", passwd, &required_size);
        if (err == ESP_OK)
        {
            ESP_LOGI(TAG, "SUCCESS READING THE WIFI PASSWORD");
            return passwd;
        }
    }
    ESP_LOGI(TAG, "FAILED READING THE WIFI PASSWORD");
    passwd = nullptr;
    return passwd;
}

void myNvs::my_nvs_cleanup()
{
    nvs_close(storage_handle);
}

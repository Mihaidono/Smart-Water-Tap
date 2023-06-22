#include "myHttp.h"
#include "myControl.h"

static const char *TAG = "HTTP-Server";

myHttp::~myHttp()
{
    stop_webserver(this->server);
}

esp_err_t myHttp::default_handler(httpd_req_t *req)
{
    /* this will form a json object and send the name of the device */
    cJSON *root = cJSON_CreateObject();

    cJSON_AddStringToObject(root, "device-name", myControl::getInstance().get_device_name());
    char *resp = cJSON_Print(root);
    cJSON_Delete(root);

    httpd_resp_set_type(req, "application/json");

    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

esp_err_t myHttp::get_tap_state_handler(httpd_req_t *req)
{
    /* this will form a json object and send the name: name and state: state */
    cJSON *root = cJSON_CreateObject();

    cJSON_AddStringToObject(root, "device-name", myControl::getInstance().get_device_name());
    cJSON_AddStringToObject(root, "state", myControl::getInstance().get_motor().get_last_state());
    cJSON_AddStringToObject(root, "device-type", myControl::getInstance().get_device_type());

    char *resp = cJSON_Print(root);
    cJSON_Delete(root);

    httpd_resp_set_type(req, "application/json");

    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

esp_err_t myHttp::change_tap_state_handler(httpd_req_t *req)
{
    char content[100];
    size_t content_size = MIN(req->content_len, sizeof(content));
    int ret = httpd_req_recv(req, content, content_size);

    cJSON *json = cJSON_Parse(content);

    if (json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }

        cJSON_Delete(json);
    }

    const cJSON *new_state = cJSON_GetObjectItem(json, "state");
    if (cJSON_IsString(new_state) && (new_state->valuestring != NULL))
    {
        if (strcmp("open", myControl::getInstance().get_motor().get_last_state()) != 0 &&
            strcmp(new_state->valuestring, "open") == 0)
        {
            myControl::getInstance().get_motor().step(130);
            myControl::getInstance().get_motor().set_last_state("open");
            myControl::getInstance().get_nvs_storage().store_state(myControl::getInstance().get_motor().get_last_state());
            //ESP_LOGI(TAG, "LAST STATE: %s", myControl::getInstance().get_motor().get_last_state());
        }
        else if (strcmp("close", myControl::getInstance().get_motor().get_last_state()) != 0 &&
                 strcmp(new_state->valuestring, "close") == 0)
        {
            myControl::getInstance().get_motor().step(-130);
            myControl::getInstance().get_motor().set_last_state("close");
            myControl::getInstance().get_nvs_storage().store_state(myControl::getInstance().get_motor().get_last_state());
            //ESP_LOGI(TAG, "LAST STATE: %s", myControl::getInstance().get_motor().get_last_state());
        }
        else
        {
            ESP_LOGI(TAG, "ERROR CHANGING STATE");
        }
    }

    if (ret <= 0)
    { /* 0 return value indicates connection closed */
        /* Check if timeout occurred */
        if (ret == HTTPD_SOCK_ERR_TIMEOUT)
        {
            /* In case of timeout one can choose to retry calling
             * httpd_req_recv(), but to keep it simple, here we
             * respond with an HTTP 408 (Request Timeout) error */
            httpd_resp_send_408(req);
        }
        /* In case of error, returning ESP_FAIL will
         * ensure that the underlying socket is closed */
        return ESP_FAIL;
    }

    cJSON_Delete(json);
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

httpd_handle_t myHttp::start_webserver()
{
    this->server = NULL;
    /* Generate default configuration */
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    /* Empty handle to esp_http_server */

    /* Start the httpd server */
    if (httpd_start(&server, &config) == ESP_OK)
    {
        /* Register URI handlers */
        httpd_register_uri_handler(this->server, &state_uri);
        httpd_register_uri_handler(this->server, &rotate_uri);
        httpd_register_uri_handler(this->server, &default_uri);
    }
    /* If server failed to start, handle will be NULL */
    return this->server;
}

/* Function for stopping the webserver */
void myHttp::stop_webserver(httpd_handle_t server)
{
    if (this->server)
    {
        /* Stop the httpd server */
        httpd_stop(this->server);
    }
}
#ifndef STUDENT_H
#define STUDENT_H

#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "nvs_flash.h"
#include <esp_http_server.h>
#include <esp_err.h>
#include <cstring>
#include <cctype>
#include "cJSON.h"

class myHttp
{
private:
    httpd_handle_t server;

    static esp_err_t get_tap_state_handler(httpd_req_t *);
    static esp_err_t change_tap_state_handler(httpd_req_t *);
    static esp_err_t default_handler(httpd_req_t *);

    httpd_uri_t state_uri = {
        .uri = "/state",
        .method = HTTP_GET,
        .handler = get_tap_state_handler,
        .user_ctx = NULL};

    httpd_uri_t rotate_uri = {
        .uri = "/rotate",
        .method = HTTP_POST,
        .handler = change_tap_state_handler,
        .user_ctx = NULL};

    httpd_uri_t default_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = default_handler,
        .user_ctx = NULL};

public:
    myHttp() {}
    ~myHttp();

    httpd_handle_t start_webserver();
    void stop_webserver(httpd_handle_t);
};
#endif
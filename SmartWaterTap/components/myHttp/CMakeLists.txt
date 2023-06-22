idf_component_register(SRCS "myHttp.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_http_server
                    REQUIRES json
                    REQUIRES nvs_flash
                    REQUIRES esp_event
                    REQUIRES myControl
                    )


idf_component_register(SRCS "myWifi.cpp"
                    INCLUDE_DIRS "include"
					REQUIRES esp_wifi
                    REQUIRES myHttp
                    )


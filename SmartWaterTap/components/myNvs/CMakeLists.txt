idf_component_register(SRCS "myNvs.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES nvs_flash
                    REQUIRES myControl
                    )
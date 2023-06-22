idf_component_register(SRCS "myControl.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES myStepper
                    REQUIRES myHttp
                    REQUIRES myWifi
                    REQUIRES myNvs
                    )

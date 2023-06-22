#include "myControl.h"

void myControl::init_SmartWaterTap()
{
    this->nvs_storage.init_myNvs();
    this->wifi_server.wifi_init_sta();
    if (this->wifi_server.isWifiConnected())
    {
        this->http_server.start_webserver();
        myStepper new_Motor_instance(16, 17, 18, 19);
        this->motor = new_Motor_instance;
        if (nvs_storage.get_stored_state())
        {
            this->motor.set_last_state(nvs_storage.get_stored_state());
        }
        else
        {
            this->motor.set_last_state("open");
        }
    }
}

myStepper myControl::get_motor()
{
    return this->motor;
}

myWifi myControl::get_wifi_server()
{
    return this->wifi_server;
}

myHttp myControl::get_http_server()
{
    return this->http_server;
}

myNvs myControl::get_nvs_storage()
{
    return this->nvs_storage;
}

char *myControl::get_device_name()
{
    return DEVICE_NAME;
}

char *myControl::get_device_type()
{
    return DEVICE_TYPE;
}

#include "myHttp.h"
#include "myStepper.h"
#include "myWifi.h"
#include "myNvs.h"

//change device name for every new device before flashing
//#define DEVICE_NAME "G PDF 103"
#define DEVICE_NAME "PWM507"

//#define DEVICE_TYPE "FRIDGE"
//#define DEVICE_TYPE "DRYER"
//#define DEVICE_TYPE "DISH_WASHER"
#define DEVICE_TYPE "WASHING_MACHINE"

class myControl
{
public:
    static myControl &getInstance()
    {
        static myControl instance; // Guaranteed to be destroyed.
                                   // Instantiated on first use.
        return instance;
    }

private:
    myControl() {}

    myControl(myControl const &);
    void operator=(myControl const &);

    myWifi wifi_server;
    myStepper motor;
    myHttp http_server;
    myNvs nvs_storage;

public:
    void init_SmartWaterTap();

    myStepper get_motor();
    myWifi get_wifi_server();
    myHttp get_http_server();
    myNvs get_nvs_storage();
    char *get_device_name();
    char *get_device_type();
};

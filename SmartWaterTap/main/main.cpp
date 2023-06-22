#include "myControl.h"

extern "C"
{
    void app_main();
}

void app_main(void)
{
    myControl::getInstance().init_SmartWaterTap();
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

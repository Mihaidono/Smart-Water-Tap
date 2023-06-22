#include <stdio.h>
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <rom/ets_sys.h>
#include <esp_log.h>
#include <cstring>

class myStepper
{
private:
    int stepper_pin_1;
    int stepper_pin_2;
    int stepper_pin_3;
    int stepper_pin_4;

    int current_step;
    char *last_state;

    void init_Stepper();
    void take_step();

public:
    myStepper() {}
    myStepper(int, int, int, int);

    void step(int);
    char *get_last_state();
    void set_last_state(char *);
    void release_motor();
};
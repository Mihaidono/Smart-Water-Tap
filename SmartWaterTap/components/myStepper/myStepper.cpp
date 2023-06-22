#include "myStepper.h"

static const char *TAG = "Stepper-Motor";

myStepper::myStepper(int pin1, int pin2, int pin3, int pin4)
{
    this->stepper_pin_1 = pin1;
    this->stepper_pin_2 = pin2;
    this->stepper_pin_3 = pin3;
    this->stepper_pin_4 = pin4;

    this->current_step = 0;

    init_Stepper();
}

char *myStepper::get_last_state()
{
    return this->last_state;
}

void myStepper::set_last_state(char *last_state)
{
    strcpy(this->last_state, last_state);
}

void myStepper::init_Stepper()
{
    gpio_reset_pin((gpio_num_t)this->stepper_pin_1);
    gpio_set_direction((gpio_num_t)this->stepper_pin_1, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)this->stepper_pin_1, 0);

    gpio_reset_pin((gpio_num_t)this->stepper_pin_2);
    gpio_set_direction((gpio_num_t)this->stepper_pin_2, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)this->stepper_pin_2, 0);

    gpio_reset_pin((gpio_num_t)this->stepper_pin_3);
    gpio_set_direction((gpio_num_t)this->stepper_pin_3, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)this->stepper_pin_3, 0);

    gpio_reset_pin((gpio_num_t)this->stepper_pin_4);
    gpio_set_direction((gpio_num_t)this->stepper_pin_4, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)this->stepper_pin_4, 0);
}

void myStepper::step(int steps)
{
    if (steps > 0)
    {
        ESP_LOGI(TAG, "going clockwise");
        last_state = "closed";
        for (int i = 0; i < abs(steps); i++)
        {
            for (int j = 0; j <= 7; j++)
            {
                this->current_step = j;
                take_step();
                ets_delay_us(800);
            }
            release_motor();
        }
        return;
    }
    else if (steps < 0)
    {
        ESP_LOGI(TAG, "going counter-clockwise");
        last_state = "opened";
        for (int i = 0; i < abs(steps); i++)
        {
            for (int j = 7; j >= 0; j--)
            {
                this->current_step = j;
                take_step();
                ets_delay_us(800);
            }
            release_motor();
        }
        return;
    }
}

void myStepper::take_step()
{

    switch (this->current_step)
    {
    case 0:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 1);
        break;
    case 1:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 1);
        break;
    case 2:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 0);
        break;
    case 3:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 0);
        break;
    case 4:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 0);
        break;
    case 5:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 0);
        break;
    case 6:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 0);
        break;
    case 7:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 1);
        break;
    default:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 0);
        ESP_LOGI(TAG, "steps out of bounds!");
        break;
    }
}

/* void myStepper::take_step()
{
    switch (this->current_step)
    {
    case 0:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 0);
        break;
    case 1:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 0);
        break;
    case 2:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 1);
        break;
    case 3:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 1);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 1);
        break;
    default:
        gpio_set_level((gpio_num_t)this->stepper_pin_1, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_2, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_3, 0);
        gpio_set_level((gpio_num_t)this->stepper_pin_4, 0);
        ESP_LOGI(TAG, "steps out of bounds!");
        break;
    }
} */

void myStepper::release_motor()
{
    gpio_set_level((gpio_num_t)this->stepper_pin_1, 0);
    gpio_set_level((gpio_num_t)this->stepper_pin_2, 0);
    gpio_set_level((gpio_num_t)this->stepper_pin_3, 0);
    gpio_set_level((gpio_num_t)this->stepper_pin_4, 0);
    // Add a delay here if needed to ensure the motor has released completely
    ets_delay_us(1000);
}
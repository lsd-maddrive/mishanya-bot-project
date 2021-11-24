#include <lld_control_servo.h>

#define T 10000 //period pwm
#define F 1000000 //frequency Tim

int16_t duty_cycle = 0;
bool init = false;

/*** PWM config***/
PWMConfig pwm1conf = {
    .frequency = F,
    .period = T,
    .callback = NULL,
    .channels = {
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH,    .callback = NULL}
                 },
    .cr2 = 0,
    .dier = 0
};

void lld_control_servo_init(ioline_t line)
{
    if(init)
    return;
    palSetLineMode(line,PAL_MODE_ALTERNATE(1));
    pwmStart(&PWMD1,&pwm1conf);

    init = true;
}

void lld_control_servo_hand(int16_t duty_cycle, uint16_t left_limit,
                            uint16_t right_limit, uint8_t channel)
{
    duty_cycle = CLIP_VALUE(duty_cycle,left_limit,right_limit);
    pwmEnableChannel(&PWMD1,channel,duty_cycle);
}


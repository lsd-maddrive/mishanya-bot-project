#ifndef INCLUDE_LLD_CONTROL_SERVO_H_
#define INCLUDE_LLD_CONTROL_SERVO_H_

#include <common.h>


typedef struct
{
    struct
    {
        PWMDriver* pwm_ptr;
        uint8_t channel;
        ioline_t line;
    }low_level;

    struct
    {
        uint16_t low_hand_limit;
        uint16_t high_hand_limit;
    }limits;

} servo_t;

void servo_init(servo_t* servo, PWMDriver* pwm_ptr, uint8_t channel, ioline_t line);
void servo_set_duty(servo_t* servo, uint16_t duty_cycle);
uint16_t servo_get_current_duty(servo_t* servo);
uint16_t servo_get_low_duty(servo_t* servo);
uint16_t servo_get_high_duty(servo_t* servo);
void servo_set_low_duty(servo_t* servo, uint16_t low_duty);
void servo_set_high_duty(servo_t* servo, uint16_t high_duty);

#endif

#include <lld_control_servo.h>

#define DEFAULT_MIN_DUTY 900U
#define DEFAULT_MAX_DUTY 2100U


void servo_init(servo_t* servo, PWMDriver* pwm_ptr, uint8_t channel, ioline_t line)
{

    servo->low_level.channel = channel;
    servo->low_level.pwm_ptr = pwm_ptr;
    servo->low_level.line = line;

    servo->limits.high_hand_limit = DEFAULT_MAX_DUTY;
    servo->limits.low_hand_limit = DEFAULT_MIN_DUTY;
}

void servo_set_duty(servo_t* servo, uint16_t duty_cycle)
{
    duty_cycle = CLIP_VALUE(duty_cycle,servo->limits.low_hand_limit,
                            servo->limits.high_hand_limit);

    pwmEnableChannel(servo->low_level.pwm_ptr,servo->low_level.channel,duty_cycle);

}

uint16_t servo_get_current_duty(servo_t* servo)
{
    return servo->low_level.pwm_ptr->tim->CCR[servo->low_level.channel];
}

uint16_t servo_get_low_duty(servo_t* servo)
{
    return servo->limits.low_hand_limit;
}

uint16_t servo_get_high_duty(servo_t* servo)
{
    return servo->limits.high_hand_limit;
}

void servo_set_low_duty(servo_t* servo, uint16_t low_duty)
{
    servo->limits.low_hand_limit = low_duty;
}

void servo_set_high_duty(servo_t* servo, uint16_t high_duty)
{
    servo->limits.high_hand_limit = high_duty;
}
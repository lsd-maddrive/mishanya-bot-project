#include <lld_control_servo.h>
#include <common.h>

#define T 10000 //period pwm
#define F 1000000 //frequency Tim

int16_t duty_cycle = 0;
bool init = false;

/*** PWM config***/
PWMConfig pwm3conf = {
    .frequency = F,
    .period = T,
    .callback = NULL,
    .channels = {
                 {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                 {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
                 {.mode = PWM_OUTPUT_DISABLED,  .callback = NULL}
                 },
    .cr2 = 0,
    .dier = 0
};
PWMConfig pwm4conf = {
    .frequency = F,
    .period = T,
    .callback = NULL,
    .channels = {
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                 {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH,  .callback = NULL}
                 },
    .cr2 = 0,
    .dier = 0
};
/**
 *  @servo in the left hand
 */
servo_arm left_hand =
{
      .channel = 0,
      .line = PAL_LINE(GPIOB,6),
      .low_hand_limit = 1110,
      .high_hand_limit = 1620
};

/**
 *  @servo in the left wrist
 */
servo_arm left_wrist =
{
      .channel = 2,
      .line = PAL_LINE(GPIOB,8),
      .low_hand_limit = 900,
      .high_hand_limit = 2100
};
/**
 *  @servo in the right hand
 */
servo_arm right_hand =
{
      .channel = 3,
      .line = PAL_LINE(GPIOB,9),
      .low_hand_limit = 1110,
      .high_hand_limit = 1620
};

/**
 *  @servo in the right wrist
 */
servo_arm right_wrist =
{
      .channel = 1,
      .line = PAL_LINE(GPIOB,5),
      .low_hand_limit = 900,
      .high_hand_limit = 2100
};

void lld_control_servo_init(void)
{
    if(init)
    return;

    palSetLineMode(left_hand.line,PAL_MODE_ALTERNATE(2));
    palSetLineMode(right_hand.line,PAL_MODE_ALTERNATE(2));
    palSetLineMode(left_wrist.line,PAL_MODE_ALTERNATE(2));
    palSetLineMode(right_wrist.line,PAL_MODE_ALTERNATE(2));
    pwmStart(&PWMD3,&pwm3conf);
    pwmStart(&PWMD4,&pwm4conf);

    init = true;
}

void lld_control_servo(int16_t duty_cycle, servo_arm *servo)
{
    duty_cycle = CLIP_VALUE(duty_cycle,servo->low_hand_limit,
                            servo->high_hand_limit);
    if(servo == &right_wrist)
      pwmEnableChannel(&PWMD3,servo->channel,duty_cycle);
    else
      pwmEnableChannel(&PWMD4,servo->channel,duty_cycle);
}

void lld_set_dutycycle_servo(int16_t duty_cycle, type_servo servo_t)
{
    switch(servo_t)
    {
        case LEFT_HAND:
            lld_control_servo(duty_cycle, &left_hand);
            break;
        case LEFT_WRIST:
            lld_control_servo(duty_cycle, &left_wrist);
            break;
        case RIGHT_HAND:
            lld_control_servo(duty_cycle, &right_hand);
            break;
        case RIGHT_WRIST:
            lld_control_servo(duty_cycle, &right_wrist);
            break;
        default: ;
    }
}

uint16_t get_servo_low_limit(type_servo servo_t)
{
    uint16_t low = 0;
    servo_arm *servo;
    switch(servo_t)
    {
        case LEFT_HAND:
             servo = &left_hand;
             low = servo->low_hand_limit;
             break;
        case LEFT_WRIST:
             servo = &left_wrist;
             low = servo->low_hand_limit;
             break;
        case RIGHT_WRIST:
             servo = &right_wrist;
             low = servo->low_hand_limit;
             break;
        case RIGHT_HAND:
             servo = &right_hand;
             low = servo->low_hand_limit;
             break;

    }
    return low;
}

uint16_t get_servo_high_limit(type_servo servo_t)
{
    uint16_t high = 0;
    servo_arm *servo;
    switch(servo_t)
    {
        case LEFT_HAND:
             servo = &left_hand;
             high = servo->high_hand_limit;
             break;
        case LEFT_WRIST:
             servo = &left_wrist;
             high = servo->high_hand_limit;
             break;
        case RIGHT_WRIST:
             servo = &right_wrist;
             high = servo->high_hand_limit;
             break;
        case RIGHT_HAND:
             servo = &right_hand;
             high = servo->high_hand_limit;
             break;
    }
    return high;
}
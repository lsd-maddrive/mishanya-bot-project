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
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH,    .callback = NULL}
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
      .line = PAL_LINE(GPIOC,6),
      .low_hand_limit = 1110,
      .high_hand_limit = 1620
};

/**
 *  @servo in the left wrist
 */
servo_arm left_wrist =
{
      .channel = 1,
      .line = PAL_LINE(GPIOC,7),
      .low_hand_limit = 900,
      .high_hand_limit = 2100
};
/**
 *  @servo in the right hand
 */
servo_arm right_hand =
{
      .channel = 2,
      .line = PAL_LINE(GPIOC,8),
      .low_hand_limit = 1110,
      .high_hand_limit = 1620
};

/**
 *  @servo in the right wrist
 */
servo_arm right_wrist =
{
      .channel = 3,
      .line = PAL_LINE(GPIOC,9),
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

    init = true;
}

void lld_control_servo(int16_t duty_cycle, servo_arm *servo)
{
    duty_cycle = CLIP_VALUE(duty_cycle,servo->low_hand_limit,
                            servo->high_hand_limit);
    pwmEnableChannel(&PWMD3,servo->channel,duty_cycle);
}

void setServoPtr(int16_t duty_cycle, int8_t servo_t)
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

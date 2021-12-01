#include <lld_control_servo.h>

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
      .left_hand_limit = 1110,
      .right_hand_limit = 1620
};

/**
 *  @servo in the left wrist
 */
servo_arm left_wrist =
{
      .channel = 1,
      .line = PAL_LINE(GPIOC,7),
      .left_hand_limit = 900,
      .right_hand_limit = 2100
};
/**
 *  @servo in the right hand
 */
servo_arm right_hand =
{
      .channel = 2,
      .line = PAL_LINE(GPIOC,8),
      .left_hand_limit = 1110,
      .right_hand_limit = 1620
};

/**
 *  @servo in the right wrist
 */
servo_arm right_wrist =
{
      .channel = 3,
      .line = PAL_LINE(GPIOC,9),
      .left_hand_limit = 900,
      .right_hand_limit = 2100
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

void lld_control_servo_hand(int16_t duty_cycle, servo_arm *servo)
{
    duty_cycle = CLIP_VALUE(duty_cycle,servo->left_hand_limit,
                            servo->right_hand_limit);
    pwmEnableChannel(&PWMD3,servo->channel,duty_cycle);
}


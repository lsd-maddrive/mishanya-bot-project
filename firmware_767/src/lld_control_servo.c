#include <lld_control_servo.h>

//#define PWM_SERVO_HAND PAL_LINE(GPIOE,9)
#define PWM_SERVO_WRIST PAL_LINE(GPIOE,11)
#define T 10000
#define F 1000000

int16_t duty_cycle = 0;
bool init = false;

/*** PWM config***/
PWMConfig pwm1conf = {
    .frequency = F,
    .period = T,
    .callback = NULL,
    .channels = {
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},//PE9
                 {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},//PE11
                 {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
                 {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL}
                 },
    .cr2 = 0,
    .dier = 0
};


lhs left_hand =
{
      .GPIOx = GPIOE,
      .pin = 9,
      .left_hand_limits = 1110,
      .right_hand_limits = 1620
};
/**
 *  @brief Initialize PWM and pin
 *  @note variable init for protection
 */
void lld_control_servo_init(void)
{
    if(init)
    return;

    palSetLineMode(PAL_LINE(left_hand.GPIOx,left_hand.pin),PAL_MODE_ALTERNATE(1));
    palSetLineMode(PWM_SERVO_WRIST, PAL_MODE_ALTERNATE(1));
    pwmStart(&PWMD1,&pwm1conf);

    init = true;
}

/**
 * @brief Set raw duty cycle for servo in wrist
 * @args duty_cycle is raw value
 */
void lld_control_servo_wrist(int16_t duty_cycle)
{

//    duty_cycle = CLIP_VALUE(duty_cycle, lh_s->left_wrist_limits,
//                            lh_s->right_wrist_limits);
    pwmEnableChannel(&PWMD1,1,duty_cycle);
}

/**
 * @brief Set raw duty cycle for servo in hand
 * @args duty_cycle is raw value
 */
void lld_control_servo_hand(int16_t duty_cycle)
{
    duty_cycle = CLIP_VALUE(duty_cycle,left_hand.left_hand_limits,
                            left_hand.right_hand_limits);
    pwmEnableChannel(&PWMD1,0,duty_cycle);
}


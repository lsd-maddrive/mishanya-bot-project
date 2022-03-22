#include <lld_bb_driver.h>
#include <lld_bridge_system.h>

#define PWM_FREQ 1000000
#define PWM_PERIOD 1000
#define DIRECT PAL_LINE(GPIOB,3)
#define REVERSE PAL_LINE(GPIOB,4)
#define PWM1 PAL_LINE(GPIOA,8) //TIM_CH1
#define PWM2 PAL_LINE(GPIOA,7) //TIM_CH1N

control_driver_t Wheel_num[3];

const pwm_ctx_t pwm_ctx_bb = {
    .pwm_conf = {
    .frequency = PWM_FREQ,
    .period    = PWM_PERIOD,
    .callback  = NULL,
    .channels  = {
      {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
      {.mode = PWM_OUTPUT_DISABLED, NULL}
    },
    .cr2        = 0,
    .bdtr = 0b11010110,
    .dier       = 0
  }
};

const pwm_channel_t ch_pwm_bb_wheel_1 = {
    .ch_pwm_1 = 0,
    .alt_func_1 = 1,
    .alt_func_2 = 1,
    .driver_ptr = &PWMD1
};

const line_driver_t pin_line_bb_wheel_1 = {
    .PWM_1 = PWM1,
    .PWM_2 = PWM2,
    .digit_1 = DIRECT,
    .digit_2 = REVERSE
};

const control_driver_t control_bb_wheel_1 = {
    .pwm_setting_ctx = ch_pwm_bb_wheel_1,
    .line_control = pin_line_bb_wheel_1
};

Wheel_num[0] = control_bb_wheel_1;

const pwm_channel_t ch_pwm_bb_wheel_2 = {
    .ch_pwm_1 = 0,
    .alt_func_1 = 1,
    .alt_func_2 = 1,
    .driver_ptr = &PWMD1
};

const line_driver_t pin_line_bb_wheel_2 = {
    .PWM_1 = PWM1,
    .PWM_2 = PWM2,
    .digit_1 = DIRECT,
    .digit_2 = REVERSE
};

const control_driver_t control_bb_wheel_2 = {
    .pwm_setting_ctx = ch_pwm_bb_wheel_2,
    .line_control = pin_line_bb_wheel_2
};

Wheel_num[1] = control_bb_wheel_2;

const pwm_channel_t ch_pwm_bb_wheel_3 = {
    .ch_pwm_1 = 0,
    .alt_func_1 = 1,
    .alt_func_2 = 1,
    .driver_ptr = &PWMD1
};

const line_driver_t pin_line_bb_wheel_3 = {
    .PWM_1 = PWM1,
    .PWM_2 = PWM2,
    .digit_1 = DIRECT,
    .digit_2 = REVERSE
};

const control_driver_t control_bb_wheel_3 = {
    .pwm_setting_ctx = ch_pwm_bb_wheel_3,
    .line_control = pin_line_bb_wheel_3
};

Wheel_num[2] = control_bb_wheel_3;

void lld_bb_init_driver(void)
{
    palSetLineMode(control_bb_wheel_1.line_control.PWM_1, PAL_MODE_ALTERNATE(control_bb_wheel_1.pwm_setting_ctx.alt_func_1));
    palSetLineMode(control_bb_wheel_1.line_control.PWM_2, PAL_MODE_ALTERNATE(control_bb_wheel_1.pwm_setting_ctx.alt_func_2));
    palSetLineMode(control_bb_wheel_1.line_control.digit_1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(control_bb_wheel_1.line_control.digit_2, PAL_MODE_OUTPUT_PUSHPULL);
}

void lld_bb_driver_direct(const control_driver_t* control, uint16_t period)
{

	palWriteLine(control->line_control.digit_1, PAL_LOW);
	palWriteLine(control->line_control.digit_2, PAL_HIGH);
    pwmEnableChannel(control->pwm_setting_ctx.pwm_ch.driver_ptr, control->pwm_setting_ctx.pwm_ch.ch_pwm_1, period);

}

void lld_bb_driver_reverse(const control_driver_t* control, uint16_t period)
{

	palWriteLine(control->line_control.digit_1, PAL_HIGH);
	palWriteLine(control->line_control.digit_2, PAL_LOW);
	pwmEnableChannel(control->pwm_setting_ctx.pwm_ch.driver_ptr, control->pwm_setting_ctx.pwm_ch.ch_pwm_1, period);

}

void lld_bb_driver_off(const control_driver_t* control)
{

	palWriteLine(control->line_control.digit_1, PAL_LOW);
	palWriteLine(control->line_control.digit_2, PAL_LOW);
	pwmDisableChannel(control->pwm_setting_ctx.pwm_ch.driver_ptr, control->pwm_setting_ctx.pwm_ch.ch_pwm_1);
}

void lld_set_diver_bb_direct(uint16_t period, type_wheel wheel_t)
{
    switch(wheel_t)
    {
        case WHEEL_1:
            lld_bb_driver_direct(&Wheel_num[0], period);
            break;
        case WHEEL_2:
            lld_bb_driver_direct(&Wheel_num[1], period);
            break;
        case WHEEL_3:
            lld_bb_driver_direct(&Wheel_num[2], period);
            break;
        default: ;
    }
}

void lld_set_diver_bb_reverse(uint16_t period, type_wheel wheel_t)
{
    switch(wheel_t)
    {
        case WHEEL_1:
            lld_bb_driver_reverse(&Wheel_num[0], period);
            break;
        case WHEEL_2:
            lld_bb_driver_reverse(&Wheel_num[1], period);
            break;
        case WHEEL_3:
            lld_bb_driver_reverse(&Wheel_num[2], period);
            break;
        default: ;
    }
}

void lld_set_diver_bb_off(type_wheel wheel_t)
{
    switch(wheel_t)
    {
        case WHEEL_1:
            lld_bb_driver_off(&Wheel_num[0]);
            break;
        case WHEEL_2:
            lld_bb_driver_off(&Wheel_num[1]);
            break;
        case WHEEL_3:
            lld_bb_driver_off(&Wheel_num[2]);
            break;
        default: ;
    }
}




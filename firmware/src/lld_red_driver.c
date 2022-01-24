#include <lld_red_driver.h>
#include "serial.h"


void lld_red_init_driver(const arm_t *arm)
{

	control_driver_t pins = arm->arm_control;
	pwm_channel_t pwm_ch = arm->arm_ctx.pwm_ch;

    palSetLineMode(pins.PWM_1, PAL_MODE_ALTERNATE(pwm_ch.alt_func_1));

    palSetLineMode(pins.down, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(pins.up, PAL_MODE_OUTPUT_PUSHPULL);

    pwm_ctx_t pwm_ctx = arm->arm_ctx;

    pwmStart(pwm_ctx.driver_ptr, &pwm_ctx.pwm_conf);

}

void lld_red_driver_up(arm_side_t arm, const driver_ctx_t *arm_driver, uint16_t period)
{
	arm_t control = arm_driver->arm[arm];
	pwm_channel_t pwm_ch = arm_driver->arm->arm_ctx.pwm_ch;

	palWriteLine(control.arm_control.up, PAL_LOW);
	palWriteLine(control.arm_control.down, PAL_HIGH);
	pwmEnableChannel(control.arm_ctx.driver_ptr, pwm_ch.ch_pwm_1, period);
}

void lld_red_driver_down(arm_side_t side, const driver_ctx_t *arm_driver, uint16_t period)
{
	arm_t control = arm_driver->arm[side];
	pwm_channel_t pwm_ch = arm_driver->arm->arm_ctx.pwm_ch;

	palWriteLine(control.arm_control.up, PAL_HIGH);
	palWriteLine(control.arm_control.down, PAL_LOW);
	pwmEnableChannel(control.arm_ctx.driver_ptr, pwm_ch.ch_pwm_1, period);
}

void lld_red_driver_off(arm_side_t side, const driver_ctx_t *arm_driver)
{
	arm_t control = arm_driver->arm[side];
	pwm_channel_t pwm_ch = arm_driver->arm->arm_ctx.pwm_ch;

	palWriteLine(control.arm_control.up, PAL_LOW);
	palWriteLine(control.arm_control.down, PAL_LOW);
	pwmDisableChannel(control.arm_ctx.driver_ptr, pwm_ch.ch_pwm_1);
}


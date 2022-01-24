#include <lld_bb_driver.h>


void lld_bb_init_driver(const arm_t *arm)
{

	control_driver_t pins = arm->arm_control;
	pwm_channel_t pwm_ch = arm->arm_ctx.pwm_ch;

    palSetLineMode(pins.PWM_1, PAL_MODE_ALTERNATE(pwm_ch.alt_func_1));
    palSetLineMode(pins.PWM_2, PAL_MODE_ALTERNATE(pwm_ch.alt_func_2));

    palSetLineMode(pins.down, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(pins.up, PAL_MODE_OUTPUT_PUSHPULL);

    const pwm_ctx_t pwm_ctx = arm->arm_ctx;

    pwmStart(pwm_ctx.driver_ptr, &pwm_ctx.pwm_conf);

}

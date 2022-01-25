#include <lld_red_driver.h>



void lld_red_init_driver(const line_driver_t* pins, const pwm_ctx_t* pwm_ctx)
{

    palSetLineMode(pins->PWM_1, PAL_MODE_ALTERNATE(pwm_ctx->pwm_ch.alt_func_1));

    palSetLineMode(pins->digit_2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(pins->digit_1, PAL_MODE_OUTPUT_PUSHPULL);


    pwmStart(pwm_ctx->driver_ptr, &pwm_ctx->pwm_conf);

}

void lld_red_driver_up(const control_driver_t* control, const pwm_channel_t* pwm_ch, uint16_t period)
{

	palWriteLine(control->line_control.digit_1, PAL_LOW);
	palWriteLine(control->line_control.digit_2, PAL_HIGH);
	pwmEnableChannel(control->arm_ctx.driver_ptr, pwm_ch->ch_pwm_1, period);

}


void lld_red_driver_down(const control_driver_t* control, const pwm_channel_t* pwm_ch, uint16_t period)
{

	palWriteLine(control->line_control.digit_1, PAL_HIGH);
	palWriteLine(control->line_control.digit_2, PAL_LOW);
	pwmEnableChannel(control->arm_ctx.driver_ptr, pwm_ch->ch_pwm_1, period);

}


void lld_red_driver_off(const control_driver_t* control, const pwm_channel_t* pwm_ch)
{

	palWriteLine(control->line_control.digit_1, PAL_LOW);
	palWriteLine(control->line_control.digit_2, PAL_LOW);
	pwmDisableChannel(control->arm_ctx.driver_ptr, pwm_ch->ch_pwm_1);

}


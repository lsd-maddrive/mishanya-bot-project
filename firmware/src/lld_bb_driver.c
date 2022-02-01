#include <lld_bb_driver.h>

/**
 * @brief   initialize bridge driver type bb
 * @brief   recieve pin struct and pwm struct
 */
void lld_bb_init_driver(const line_driver_t* pins, const pwm_ctx_t* pwm_ctx)
{

	palSetLineMode(pins->PWM_1, PAL_MODE_ALTERNATE(pwm_ctx->pwm_ch.alt_func_1));
	palSetLineMode(pins->PWM_2, PAL_MODE_ALTERNATE(pwm_ctx->pwm_ch.alt_func_2));


	palSetLineMode(pins->digit_2, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLineMode(pins->digit_1, PAL_MODE_OUTPUT_PUSHPULL);


	pwmStart(pwm_ctx->driver_ptr, &pwm_ctx->pwm_conf);


}

/**
 * @brief the function open bridge driver in first direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_bb_driver_first_direction(const control_driver_t* control, const pwm_channel_t* pwm_ch, uint16_t period)
{

	palWriteLine(control->line_control.digit_1, PAL_LOW);
	palWriteLine(control->line_control.digit_2, PAL_HIGH);
	pwmEnableChannel(control->arm_ctx.driver_ptr, pwm_ch->ch_pwm_2, period);

}

/**
 * @brief the function open bridge driver in second direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_bb_driver_second_direction(const control_driver_t* control, const pwm_channel_t* pwm_ch, uint16_t period)
{

	palWriteLine(control->line_control.digit_1, PAL_HIGH);
	palWriteLine(control->line_control.digit_2, PAL_LOW);
	pwmEnableChannel(control->arm_ctx.driver_ptr, pwm_ch->ch_pwm_1, period);

}

/**
 * @brief the function disables the selected direction
 * @brief recieve control struct, pwm channel
 */
void lld_bb_driver_off(const control_driver_t* control, const pwm_channel_t* pwm_ch)
{

	palWriteLine(control->line_control.digit_1, PAL_LOW);
	palWriteLine(control->line_control.digit_2, PAL_LOW);
	pwmDisableChannel(control->arm_ctx.driver_ptr, pwm_ch->ch_pwm_1);
	pwmDisableChannel(control->arm_ctx.driver_ptr, pwm_ch->ch_pwm_2);

}

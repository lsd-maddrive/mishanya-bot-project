#include <lld_red_driver.h>

/**
 * @brief   initialize bridge driver type red
 * @brief   recieve pin struct and pwm struct
 */
void lld_red_init_driver(const line_driver_t* pins, const pwm_ctx_t* pwm_ctx)
{

  palSetLineMode(pins->hin_1, PAL_MODE_ALTERNATE(pwm_ctx->pwm_ch.alt_func_1));
  palSetLineMode(pins->lin_2, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(pins->lin_1, PAL_MODE_OUTPUT_PUSHPULL);

}

/**
 * @brief the function open bridge driver in first direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_red_driver_direct(const control_driver_t* control, const pwm_channel_t* pwm_ch, uint16_t period)
{

	palWriteLine(control->line_control.lin_1, PAL_LOW);
	palWriteLine(control->line_control.lin_2, PAL_HIGH);
	pwmEnableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_1, period);

}

/**
 * @brief the function open bridge driver in second direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_red_driver_reverse(const control_driver_t* control, const pwm_channel_t* pwm_ch, uint16_t period)
{

	palWriteLine(control->line_control.lin_1, PAL_HIGH);
	palWriteLine(control->line_control.lin_2, PAL_LOW);
	pwmEnableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_1, period);

}

/**
 * @brief the function disables the selected direction
 * @brief recieve control struct, pwm channel
 */
void lld_red_driver_off(const control_driver_t* control, const pwm_channel_t* pwm_ch)
{

	palWriteLine(control->line_control.lin_1, PAL_LOW);
	palWriteLine(control->line_control.lin_2, PAL_LOW);
	pwmDisableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_1);

}


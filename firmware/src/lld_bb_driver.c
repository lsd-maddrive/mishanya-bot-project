#include <lld_bb_driver.h>

/**
 * @brief   initialize bridge driver type bb
 * @brief   recieve pin struct and pwm struct
 */
void lld_bb_init_driver(const line_driver_t* pins, const pwm_ctx_t* pwm_ctx)
{

  palSetLineMode(pins->hin_1, PAL_MODE_ALTERNATE(pwm_ctx->pwm_ch.alt_func_1));
  palSetLineMode(pins->hin_2, PAL_MODE_ALTERNATE(pwm_ctx->pwm_ch.alt_func_2));


  palSetLineMode(pins->lin_1, PAL_MODE_ALTERNATE(pwm_ctx->pwm_ch.alt_func_1));
  palSetLineMode(pins->lin_2, PAL_MODE_ALTERNATE(pwm_ctx->pwm_ch.alt_func_2));

}

/**
 * @brief the function open bridge driver in first direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_bb_driver_direct(const control_driver_t* control, const pwm_channel_t* pwm_ch, uint16_t period)
{

  pwmEnableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_1, period*0.9);

  pwmEnableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_2, 0);

}

/**
 * @brief the function open bridge driver in second direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_bb_driver_reverse(const control_driver_t* control, const pwm_channel_t* pwm_ch, uint16_t period)
{

	pwmEnableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_1, 0);

  pwmEnableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_2, period*0.9);

}

/**
 * @brief the function disables the selected direction
 * @brief recieve control struct, pwm channel
 */
void lld_bb_driver_off(const control_driver_t* control, const pwm_channel_t* pwm_ch)
{

	pwmDisableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_1);
	pwmDisableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_2);


}

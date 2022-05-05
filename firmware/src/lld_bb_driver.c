#include <lld_bb_driver.h>

#define POWER_LIMIT 0.9

/**
 * @details initialize bridge driver type bb
 * @param[in] pins - pointer to the struct of control pins
 * @param[in] pwm_ctx - pointer to the structure of PWM config
 */
void lld_bb_init_driver(const line_driver_t* pins, const pwm_ctx_t* pwm_ctx)
{

  palSetLineMode(pins->hin_1, PAL_MODE_ALTERNATE(pwm_ctx->pwm_ch.alt_func_1));
  palSetLineMode(pins->hin_2, PAL_MODE_ALTERNATE(pwm_ctx->pwm_ch.alt_func_2));


  palSetLineMode(pins->lin_1, PAL_MODE_ALTERNATE(pwm_ctx->pwm_ch.alt_func_1));
  palSetLineMode(pins->lin_2, PAL_MODE_ALTERNATE(pwm_ctx->pwm_ch.alt_func_2));

}

/**
 * @details the function open bridge driver in first direction
 * @param[in] control - pointer to the control struct of driver
 * @param[in] pwm_ch - pointer to the structure of PWM channel
 * @param[in] period - PWM period
 */
void lld_bb_driver_direct(const control_driver_t* control, const pwm_channel_t* pwm_ch, uint16_t period)
{

  pwmEnableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_1, period*POWER_LIMIT);

  pwmEnableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_2, 0);

}

/**
 * @details the function open bridge driver in reverse direction
 * @param[in] control - pointer to the control struct of driver
 * @param[in] pwm_ch - pointer to the structure of PWM channel
 * @param[in] period - PWM period
 */
void lld_bb_driver_reverse(const control_driver_t* control, const pwm_channel_t* pwm_ch, uint16_t period)
{

	pwmEnableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_1, 0);

  pwmEnableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_2, period*POWER_LIMIT);

}

/**
 * @details the function disables the selected direction
 * @param[in] control - pointer to the control struct of driver
 * @param[in] pwm_ch - pointer to the structure of PWM channel
 */
void lld_bb_driver_off(const control_driver_t* control, const pwm_channel_t* pwm_ch)
{

	pwmDisableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_1);
	pwmDisableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_2);


}

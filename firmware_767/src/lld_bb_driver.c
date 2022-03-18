#include <lld_bb_driver.h>

void lld_bb_init_driver(const control_driver_t *control)
{

  palSetLineMode(control->line_control.PWM_1, PAL_MODE_ALTERNATE(control->pwm_setting_ctx.pwm_ch.alt_func_1));
  palSetLineMode(control->line_control.PWM_2, PAL_MODE_ALTERNATE(control->pwm_setting_ctx.pwm_ch.alt_func_2));


  palSetLineMode(control->line_control.digit_1, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(control->line_control.digit_2, PAL_MODE_OUTPUT_PUSHPULL);
}

void lld_bb_driver_direct(const control_driver_t* control, const pwm_channel_t* pwm_ch, uint16_t period)
{

	palWriteLine(control->line_control.digit_1, PAL_LOW);
	palWriteLine(control->line_control.digit_2, PAL_HIGH);
  pwmEnableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_1, period);

}

void lld_bb_driver_reverse(const control_driver_t* control, const pwm_channel_t* pwm_ch, uint16_t period)
{

	palWriteLine(control->line_control.digit_1, PAL_HIGH);
	palWriteLine(control->line_control.digit_2, PAL_LOW);
	pwmEnableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_1, period);

}

void lld_bb_driver_off(const control_driver_t* control, const pwm_channel_t* pwm_ch)
{

	palWriteLine(control->line_control.digit_1, PAL_LOW);
	palWriteLine(control->line_control.digit_2, PAL_LOW);
	pwmDisableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_1);
	pwmDisableChannel(control->pwm_setting_ctx.driver_ptr, pwm_ch->ch_pwm_2);

}

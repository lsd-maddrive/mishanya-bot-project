#include <lld_red_driver.h>

static void lld_red_init_line(line_driver_t* line_control);

static void lld_red_init_line(line_driver_t* line_control)
{
  palSetLineMode(line_control->red_driver_line.pwm_line, PAL_MODE_ALTERNATE(line_control->alt_func_num));
  palSetLineMode(line_control->red_driver_line.gpio_line_1, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(line_control->red_driver_line.gpio_line_2, PAL_MODE_OUTPUT_PUSHPULL);
}

/**
 * @brief   initialize bridge driver type red
 * @brief   recieve pin struct and pwm struct
 */
void lld_red_init_driver(control_driver_t* driver, PWMDriver* pwm_ptr, uint8_t ch_num)
{
  line_driver_t control = driver->control_red.red_pwm_ctx.control;

  lld_red_init_line(&control);

  control.ch_pwm_num= ch_num;

  driver->control_red.red_pwm_ctx.driver_ptr = pwm_ptr;

  driver->pwm_period = pwm_ptr->period;
}

/**
 * @brief the function open bridge driver in first direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_red_driver_direct(control_driver_t* driver, float period)
{
	line_driver_t control = driver->control_red.red_pwm_ctx.control;

	palWriteLine(control.red_driver_line.gpio_line_1, PAL_LOW);
	palWriteLine(control.red_driver_line.gpio_line_2, PAL_HIGH);

	PWMDriver* pwm_ptr = driver->control_red.red_pwm_ctx.driver_ptr;

	pwmEnableChannel(pwm_ptr, control.ch_pwm_num, (uint16_t)(period*POWER_SATURATION));
}

/**
 * @brief the function open bridge driver in second direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_red_driver_reverse(control_driver_t* driver, float period)
{

	line_driver_t control = driver->control_red.red_pwm_ctx.control;

	palWriteLine(control.red_driver_line.gpio_line_1, PAL_HIGH);
	palWriteLine(control.red_driver_line.gpio_line_2, PAL_LOW);

	PWMDriver* pwm_ptr = driver->control_red.red_pwm_ctx.driver_ptr;

	pwmEnableChannel(pwm_ptr, control.ch_pwm_num, (uint16_t)(period*POWER_SATURATION));

}

/**
 * @brief the function disables the selected direction
 * @brief recieve control struct, pwm channel
 */
void lld_red_driver_off(control_driver_t* driver)
{
	line_driver_t control = driver->control_red.red_pwm_ctx.control;

	PWMDriver* pwm_ptr = driver->control_red.red_pwm_ctx.driver_ptr;

	pwmDisableChannel(pwm_ptr, control.ch_pwm_num);

}


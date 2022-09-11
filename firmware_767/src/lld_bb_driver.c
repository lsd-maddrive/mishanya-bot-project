#include <lld_bb_driver.h>

static void lld_bb_init_line(line_driver_t* line_control);

static void lld_bb_init_line(line_driver_t* line_control)
{
  palSetLineMode(line_control->bb_driver_line.pwm_hin, PAL_MODE_ALTERNATE(line_control->alt_func_num));
  palSetLineMode(line_control->bb_driver_line.pwm_lin, PAL_MODE_ALTERNATE(line_control->alt_func_num));
}

/**
 * @brief   initialize bridge driver type bb
 * @brief   recieve pin struct and pwm struct
 */
void lld_bb_init_driver(control_driver_t* driver, PWMDriver* pwm_ptr_left_shoulder, uint8_t ch_num_left,
		PWMDriver* pwm_ptr_right_shoulder, uint8_t ch_num_right)
{
  line_driver_t left_shoulder_control = driver->control_bb.bb_pwm_ctx[LEFT_BRIDGE_SHOULDER].control;
  line_driver_t right_shoulder_control = driver->control_bb.bb_pwm_ctx[RIGHT_BRIDGE_SHOULDER].control;

  left_shoulder_control.ch_pwm_num = ch_num_left;

  right_shoulder_control.ch_pwm_num = ch_num_right;

  lld_bb_init_line(&left_shoulder_control);
  lld_bb_init_line(&right_shoulder_control);

  driver->control_bb.bb_pwm_ctx[RIGHT_BRIDGE_SHOULDER].driver_ptr = pwm_ptr_right_shoulder;

  driver->control_bb.bb_pwm_ctx[LEFT_BRIDGE_SHOULDER].driver_ptr = pwm_ptr_left_shoulder;

  driver->pwm_period = pwm_ptr_right_shoulder->period;

}

/**
 * @brief the function open bridge driver in first direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_bb_driver_direct(control_driver_t* driver, float period)
{
  line_driver_t left_shoulder = driver->control_bb.bb_pwm_ctx[LEFT_BRIDGE_SHOULDER].control;
  line_driver_t right_shoulder = driver->control_bb.bb_pwm_ctx[RIGHT_BRIDGE_SHOULDER].control;

  PWMDriver* left_pwm_ptr = driver->control_bb.bb_pwm_ctx[LEFT_BRIDGE_SHOULDER].driver_ptr;
  PWMDriver* right_pwm_ptr = driver->control_bb.bb_pwm_ctx[RIGHT_BRIDGE_SHOULDER].driver_ptr;

  pwmEnableChannel(left_pwm_ptr, left_shoulder.ch_pwm_num, (uint16_t)(period*POWER_SATURATION));
  pwmEnableChannel(right_pwm_ptr, right_shoulder.ch_pwm_num, 0);

}

/**
 * @brief the function open bridge driver in second direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_bb_driver_reverse(control_driver_t* driver, float period)
{
  line_driver_t left_shoulder = driver->control_bb.bb_pwm_ctx[LEFT_BRIDGE_SHOULDER].control;
  line_driver_t right_shoulder = driver->control_bb.bb_pwm_ctx[RIGHT_BRIDGE_SHOULDER].control;

  PWMDriver* left_pwm_ptr = driver->control_bb.bb_pwm_ctx[LEFT_BRIDGE_SHOULDER].driver_ptr;
  PWMDriver* right_pwm_ptr = driver->control_bb.bb_pwm_ctx[RIGHT_BRIDGE_SHOULDER].driver_ptr;

  pwmEnableChannel(left_pwm_ptr, left_shoulder.ch_pwm_num, 0);
  pwmEnableChannel(right_pwm_ptr, right_shoulder.ch_pwm_num, (uint16_t)(period*POWER_SATURATION));
}

/**
 * @brief the function disables the selected direction
 * @brief recieve control struct, pwm channel
 */
void lld_bb_driver_off(control_driver_t* driver)
{
	line_driver_t left_shoulder = driver->control_bb.bb_pwm_ctx[LEFT_BRIDGE_SHOULDER].control;
	line_driver_t right_shoulder = driver->control_bb.bb_pwm_ctx[RIGHT_BRIDGE_SHOULDER].control;

	PWMDriver* left_pwm_ptr = driver->control_bb.bb_pwm_ctx[LEFT_BRIDGE_SHOULDER].driver_ptr;
	PWMDriver* right_pwm_ptr = driver->control_bb.bb_pwm_ctx[RIGHT_BRIDGE_SHOULDER].driver_ptr;

	pwmDisableChannel(right_pwm_ptr, right_shoulder.ch_pwm_num);
	pwmDisableChannel(left_pwm_ptr, left_shoulder.ch_pwm_num);
}

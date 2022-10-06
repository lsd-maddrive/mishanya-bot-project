#include "part_arm_driver.h"
#include "lld_bb_driver.h"
#include "lld_red_driver.h"

/**
 * @details initialize arm driver
 * @param[in] arm_driver - pointer to the structure of the elbow or shoulder drivers
 */
void driver_init(arm_driver_ctx_t *arm_driver)
{
	line_driver_t pins_right = arm_driver->arm[RIGHT].control.line_control;
	pwm_ctx_t pwm_ctx_right = arm_driver->arm[RIGHT].control.pwm_setting_ctx;

	line_driver_t pins_left = arm_driver->arm[LEFT].control.line_control;
	pwm_ctx_t pwm_ctx_left = arm_driver->arm[LEFT].control.pwm_setting_ctx;


	if (arm_driver->type == RED)
	{

    lld_red_init_driver(&pins_right, &pwm_ctx_right);
		lld_red_init_driver(&pins_left, &pwm_ctx_left);

	}
	else
	{

		lld_bb_init_driver(&pins_right, &pwm_ctx_right);
		lld_bb_init_driver(&pins_left, &pwm_ctx_left);

	}

  pwmStart(pwm_ctx_left.driver_ptr, &pwm_ctx_left.pwm_conf);
}

/**
 * @details the function controls the raising of the hand up
 * @param[in] side - left or right side of hand
 * @param[in] arm_driver - pointer to the structure of the elbow or shoulder drivers
 * @param[in] period - PWM period
 */
void arm_up(arm_side_t side, arm_driver_ctx_t *arm_driver, uint16_t period)
{

	control_driver_t control = arm_driver->arm[side].control;
	pwm_channel_t pwm_ch = arm_driver->arm[side].control.pwm_setting_ctx.pwm_ch;

	if (arm_driver->type == RED)
    lld_red_driver_direct(&control, &pwm_ch, period);
	else
    lld_bb_driver_direct(&control, &pwm_ch, period);

}

/**
 * @details the function controls the raising of the hand down
 * @param[in] side - left or right side of hand
 * @param[in] arm_driver - pointer to the structure of the elbow or shoulder drivers
 * @param[in] period - PWM period
 */
void arm_down(arm_side_t side, arm_driver_ctx_t *arm_driver, uint16_t period)
{

	control_driver_t control = arm_driver->arm[side].control;
  pwm_channel_t pwm_ch = arm_driver->arm[side].control.pwm_setting_ctx.pwm_ch;

	if (arm_driver->type == RED)
    lld_red_driver_reverse(&control, &pwm_ch, period);
	else
    lld_bb_driver_reverse(&control, &pwm_ch, period);

}


/*!
 * @details The function disables the selected hand
 * @param[in] side - left or right side of hand
 * @param[in] arm_driver - pointer to the structure of the elbow or shoulder drivers
 */
void arm_off (arm_side_t side, arm_driver_ctx_t *arm_driver)
{

	control_driver_t control = arm_driver->arm[side].control;
	pwm_channel_t pwm_ch = arm_driver->arm->control.pwm_setting_ctx.pwm_ch;

	if (arm_driver->type == RED)
		lld_red_driver_off(&control, &pwm_ch);
	else
		lld_bb_driver_off(&control, &pwm_ch);

}

#include <part_arm_driver.h>
#include "lld_bb_driver.h"
#include "lld_red_driver.h"

/**
 * @brief   initialize arm driver
 * @brief   recieve arm struct
 */
void driver_init(arm_driver_ctx_t *arm_driver)
{
	line_driver_t pins_right_elbow = arm_driver->arm[RIGHT_ELBOW].control.line_control;
	line_driver_t pins_right_shoulder_in = arm_driver->arm[RIGHT_SHOULDER_IN].control.line_control;
	line_driver_t pins_right_shoulder_out = arm_driver->arm[RIGHT_SHOULDER_OUT].control.line_control;

	pwm_ctx_t pwm_ctx_right_elbow = arm_driver->arm[RIGHT_ELBOW].control.pwm_setting_ctx;
	pwm_ctx_t pwm_ctx_right_shoulder_in = arm_driver->arm[RIGHT_SHOULDER_IN].control.pwm_setting_ctx;
	pwm_ctx_t pwm_ctx_right_shoulder_out = arm_driver->arm[RIGHT_SHOULDER_OUT].control.pwm_setting_ctx;

	line_driver_t pins_left_elbow = arm_driver->arm[LEFT_ELBOW].control.line_control;
	line_driver_t pins_left_shoulder_in = arm_driver->arm[LEFT_SHOULDER_IN].control.line_control;
	line_driver_t pins_left_shoulder_out = arm_driver->arm[LEFT_SHOULDER_OUT].control.line_control;

	pwm_ctx_t pwm_ctx_left_elbow = arm_driver->arm[LEFT_ELBOW].control.pwm_setting_ctx;
	pwm_ctx_t pwm_ctx_left_shoulder_in = arm_driver->arm[LEFT_SHOULDER_IN].control.pwm_setting_ctx;
	pwm_ctx_t pwm_ctx_left_shoulder_out = arm_driver->arm[LEFT_SHOULDER_OUT].control.pwm_setting_ctx;

	if (arm_driver->type == RED)
	{

        lld_red_init_driver(&pins_right_elbow, &pwm_ctx_right_elbow);
		lld_red_init_driver(&pins_left_elbow, &pwm_ctx_left_elbow);

		lld_red_init_driver(&pins_right_shoulder_in, &pwm_ctx_right_shoulder_in);
		lld_red_init_driver(&pins_left_shoulder_in, &pwm_ctx_left_shoulder_in);

		lld_red_init_driver(&pins_right_shoulder_out, &pwm_ctx_right_shoulder_out);
		lld_red_init_driver(&pins_left_shoulder_out, &pwm_ctx_left_shoulder_out);
	}
	else
	{

      lld_bb_init_driver(&pins_right_elbow, &pwm_ctx_right_elbow);
      lld_bb_init_driver(&pins_left_elbow, &pwm_ctx_left_elbow);

      lld_bb_init_driver(&pins_right_shoulder_in, &pwm_ctx_right_shoulder_in);
      lld_bb_init_driver(&pins_left_shoulder_in, &pwm_ctx_left_shoulder_in);

      lld_bb_init_driver(&pins_right_shoulder_out, &pwm_ctx_right_shoulder_out);
      lld_bb_init_driver(&pins_left_shoulder_out, &pwm_ctx_left_shoulder_out);

	}
  pwmStart(pwm_ctx_left_elbow.driver_ptr, &pwm_ctx_left_elbow.pwm_conf);
  pwmStart(pwm_ctx_right_elbow.driver_ptr, &pwm_ctx_right_elbow.pwm_conf);
//  pwmStart(pwm_ctx_left_shoulder_in.driver_ptr, &pwm_ctx_left_shoulder_in.pwm_conf);
//  pwmStart(pwm_ctx_right_shoulder_in.driver_ptr, &pwm_ctx_right_shoulder_in.pwm_conf);
//  pwmStart(pwm_ctx_left_shoulder_out.driver_ptr, &pwm_ctx_left_shoulder_out.pwm_conf);
//  pwmStart(pwm_ctx_right_shoulder_out.driver_ptr, &pwm_ctx_right_shoulder_out.pwm_conf);

}

/**
 * @brief the function controls the raising of the hand up
 * @brief recieve the hand side, arm struct and the filling period
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
 * @brief the function controls the raising of the hand down
 * @brief recieve the hand side, arm struct and the filling period
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


/**
 * @brief the function disables the selected hand
 * @brief recieve the hand side, arm struct
 */
void arm_off (arm_side_t side, arm_driver_ctx_t *arm_driver)
{

	control_driver_t control = arm_driver->arm[side].control;
	pwm_channel_t pwm_ch = arm_driver->arm->control.pwm_setting_ctx.pwm_ch;
	if (arm_driver->type == RED)
	{
		lld_red_driver_off(&control, &pwm_ch);
	}
	else
		lld_bb_driver_off(&control, &pwm_ch);
}

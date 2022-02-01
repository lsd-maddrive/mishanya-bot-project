#include <arm_driver.h>
#include "lld_bb_driver.h"
#include "lld_red_driver.h"

/**
 * @brief   initialize arm driver
 * @brief   recieve arm struct
 */
void driver_init(const arm_driver_ctx_t *arm_driver)
{

	line_driver_t pins_right = arm_driver->arm[RIGHT].line_control;
	pwm_ctx_t pwm_ctx_right = arm_driver->arm[RIGHT].arm_ctx;

	line_driver_t pins_left = arm_driver->arm[LEFT].line_control;
	pwm_ctx_t pwm_ctx_left = arm_driver->arm[LEFT].arm_ctx;


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

}

/**
 * @brief the function controls the raising of the hand up
 * @brief recieve the hand side, arm struct and the filling period
 */
void arm_up(arm_side_t side, const arm_driver_ctx_t *arm_driver, uint16_t period)
{

	control_driver_t control = arm_driver->arm[side];
	pwm_channel_t pwm_ch = arm_driver->arm->arm_ctx.pwm_ch;

	if (arm_driver->type == RED)
		lld_red_driver_first_direction(&control, &pwm_ch, period);
	else
		lld_bb_driver_first_direction(&control, &pwm_ch, period);

}


/**
 * @brief the function controls the raising of the hand down
 * @brief recieve the hand side, arm struct and the filling period
 */
void arm_down(arm_side_t side, const arm_driver_ctx_t *arm_driver, uint16_t period)
{

	control_driver_t control = arm_driver->arm[side];
	pwm_channel_t pwm_ch = arm_driver->arm->arm_ctx.pwm_ch;

	if (arm_driver->type == RED)
		lld_red_driver_second_direction(&control, &pwm_ch, period);
	else
		lld_bb_driver_second_direction(&control, &pwm_ch, period);

}


/**
 * @brief the function disables the selected hand
 * @brief recieve the hand side, arm struct
 */
void arm_off (arm_side_t side, const arm_driver_ctx_t *arm_driver)
{

	control_driver_t control = arm_driver->arm[side];
	pwm_channel_t pwm_ch = arm_driver->arm->arm_ctx.pwm_ch;

	if (arm_driver->type == RED)
		lld_red_driver_off(&control, &pwm_ch);
	else
		lld_bb_driver_off(&control, &pwm_ch);

}

#include <arm_driver.h>
#include "lld_bb_driver.h"
#include "lld_red_driver.h"

/**
 * @brief   Initialize arm driver
 */
void driver_init(const arm_driver_ctx_t *arm_driver)
{

	line_driver_t pins_right = arm_driver->arm[LEFT].line_control;
	pwm_ctx_t pwm_ctx_right = arm_driver->arm[LEFT].arm_ctx;

	line_driver_t pins_left = arm_driver->arm[RIGHT].line_control;
    pwm_ctx_t pwm_ctx_left = arm_driver->arm[RIGHT].arm_ctx;


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
 * @brief recieve the hand number and the filling period
 * the function controls the raising of the hand up
 */
void arm_up(arm_side_t side, const arm_driver_ctx_t *arm_driver, uint16_t period)
{

	control_driver_t control = arm_driver->arm[side];
	pwm_channel_t pwm_ch = arm_driver->arm->arm_ctx.pwm_ch;

	if (arm_driver->type == RED)
		lld_red_driver_up(&control, &pwm_ch, period);
	else
		lld_bb_driver_up(&control, &pwm_ch, period);

}


/**
 * @brief recieve the hand number and the filling period
 * the function controls the raising of the hand down
 */
void arm_down(arm_side_t side, const arm_driver_ctx_t *arm_driver, uint16_t period)
{

	control_driver_t control = arm_driver->arm[side];
	pwm_channel_t pwm_ch = arm_driver->arm->arm_ctx.pwm_ch;

	if (arm_driver->type == RED)
		lld_red_driver_down(&control, &pwm_ch, period);
	else
		lld_red_driver_down(&control, &pwm_ch, period);
}


/**
 * @brief recieve the hand number
 * the function disables the selected hand
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

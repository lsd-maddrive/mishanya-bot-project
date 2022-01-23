#include <arm_driver.h>
#include "lld_bb_driver.h"
#include "lld_red_driver.h"
/**
 * @brief   Initialize arm driver
 */
void driver_init(const driver_ctx_t *arm_driver)
{

	if (arm_driver->type == RED)
	{

		lld_red_init_driver(&arm_driver->arm[LEFT]);
//		lld_red_init_driver(&arm_driver->arm[RIGHT]);

	}
	else
	{

		lld_bb_init_driver(&arm_driver->arm[LEFT]);
		lld_bb_init_driver(&arm_driver->arm[RIGHT]);

	}

}

/**
 * @brief recieve the hand number and the filling period
 * the function controls the raising of the hand up
 */
void arm_up(arm_side_t side, const driver_ctx_t *arm_driver, uint16_t period)
{
	arm_t control = arm_driver->arm[side];

	palWriteLine(control.arm_control.up, PAL_LOW);
	palWriteLine(control.arm_control.down, PAL_HIGH);
	pwmEnableChannel(control.arm_ctx.driver_ptr, side, period);
}
//
////
// void test_new_driver(arm_t ARM, uint16_t PWM_period)
// {
//     pwmEnableChannel(ARM_DRIVER, ARM, PWM_period);
//    palWriteLine(UP_ARM_LEFT, PAL_HIGH);
//    palWriteLine(DOWN_ARM_LEFT, PAL_LOW);
// }
//
///**
// * @brief recieve the hand number and the filling period
// * the function controls the raising of the hand down
// */
//void ARM_down(arm_t ARM, uint16_t PWM_period)
//{
//    pwmEnableChannel(ARM_DRIVER, ARM, PWM_period);
//    palWriteLine(DOWN_ARM_1, PAL_HIGH);
//    palWriteLine(UP_ARM_1, PAL_LOW);
//}
//
///**
// * @brief recieve the hand number
// * the function disables the selected hand
// */
//void Off_ARM (arm_t ARM, ioline_t)
//{
//   pwmDisableChannel(ARM_DRIVER, ARM);
//   palWriteLine(DOWN_ARM_LEFT, PAL_LOW);
//   palWriteLine(UP_ARM_LEFT, PAL_LOW);
//}

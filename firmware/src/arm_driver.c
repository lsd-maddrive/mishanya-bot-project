#include <arm_driver.h>


/**
 * @brief   Initialize arm driver
 */
void driver_init(driver_ctx_t *arm_driver)
{
	if (arm_driver->type == RED)
	{

		lld_red_init_driver(&arm_driver->left);
		lld_red_init_driver(&arm_driver->right);

	}
	else
	{

		lld_bb_init_driver(&arm_driver->left);
		lld_bb_init_driver(&arm_driver->right);
		
	}

}

/**
 * @brief recieve the hand number and the filling period
 * the function controls the raising of the hand up
 */
// void ARM_up(ARM_SIDE_t side, uint16_t PWM_period)
// {
	// driver_ctx_t *ctx = arms_ctxs[side];

//   pwmEnableChannel(ARM_DRIVER, ARM.arm, PWM_period);
//   palWriteLine(ARM.up, PAL_HIGH);
//   palWriteLine(ARM.down, PAL_LOW);
// }

//
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

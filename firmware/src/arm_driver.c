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
		lld_red_init_driver(&arm_driver->arm[RIGHT]);

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

	if (arm_driver->type == RED)
		lld_red_driver_up(side, arm_driver, period);
//	else
//		lld_bb_init_driver(&arm_driver->arm[LEFT]);

}


/**
 * @brief recieve the hand number and the filling period
 * the function controls the raising of the hand down
 */
void arm_down(arm_side_t side, const driver_ctx_t *arm_driver, uint16_t period)
{
	if (arm_driver->type == RED)
		lld_red_driver_down(side, arm_driver, period);

//	else
//		lld_bb_init_driver(&arm_driver->arm[LEFT]);
}
//
/**
 * @brief recieve the hand number
 * the function disables the selected hand
 */
void arm_off (arm_side_t side, const driver_ctx_t *arm_driver)
{

	if (arm_driver->type == RED)
		lld_red_driver_off(side, arm_driver);

//	else
//		lld_bb_init_driver(&arm_driver->arm[LEFT]);

}

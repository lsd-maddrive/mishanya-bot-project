#include <part_arm_driver.h>


/**
 * @brief the function controls the raising of the hand up
 * @brief recieve the hand side, arm struct and the filling period
 */
void arm_up(arm_side_t side, arm_ctx_t *arm_driver, uint16_t period)
{
	control_driver_t control = arm_driver->arm[side].traking_cs.control;

	if (arm_driver->type == RED)
    {
        lld_red_driver_direct(&control, period);
    }
	else
    {
        lld_bb_driver_direct(&control, period);
    }
}

/**
 * @brief the function controls the raising of the hand down
 * @brief recieve the hand side, arm struct and the filling period
 */
void arm_down(arm_side_t side, arm_ctx_t *arm_driver, uint16_t period)
{

	control_driver_t control = arm_driver->arm[side].traking_cs.control;

	if (arm_driver->type == RED)
    lld_red_driver_reverse(&control, period);
	else
    lld_bb_driver_reverse(&control, period);

}


/**
 * @brief the function disables the selected hand
 * @brief recieve the hand side, arm struct
 */
void arm_off (arm_side_t side, arm_ctx_t *arm_driver)
{

	control_driver_t control = arm_driver->arm[side].traking_cs.control;
	if (arm_driver->type == RED)
	{
		lld_red_driver_off(&control);
	}
	else
		lld_bb_driver_off(&control);
}

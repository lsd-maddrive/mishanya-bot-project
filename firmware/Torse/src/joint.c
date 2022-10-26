#include <joint.h>


/**
 * @brief the function controls the raising of the hand up
 * @brief recieve the hand side, arm struct and the filling period
 */
void joint_up(arm_side_t side, joint_t *joint, uint16_t period)
{
	control_driver_t control = joint->arm[side].traking_cs.control;

	if (joint->type == RED)
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
void joint_down(arm_side_t side, joint_t *joint, uint16_t period)
{

	control_driver_t control = joint->arm[side].traking_cs.control;

	if (joint->type == RED)
    lld_red_driver_reverse(&control, period);
	else
    lld_bb_driver_reverse(&control, period);

}


/**
 * @brief the function disables the selected hand
 * @brief recieve the hand side, arm struct
 */
void joint_off (arm_side_t side, joint_t *joint)
{

	control_driver_t control = joint->arm[side].traking_cs.control;
	if (joint->type == RED)
	{
		lld_red_driver_off(&control);
	}
	else
		lld_bb_driver_off(&control);
}

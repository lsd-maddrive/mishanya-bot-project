#include <arm_control_system.h>
static void acs_normalize_interval (arm_angle_t* arm_angle);
static float acs_normalize_angle (traking_cs_t* traking_cs, arm_angle_t* arm_angle);

/**
 * @details init arm control system 
 * @param[in] arm_driver - pointer to the structure of the elbow or shoulder (vertical/horizontal) drivers
 */
void acs_init(joint_t* joint)
{
	// left arm interval normalization
	acs_normalize_interval(&joint->arm[LEFT].arm_angle);

	// right arm interval normalization
	acs_normalize_interval(&joint->arm[RIGHT].arm_angle);

	// left arm target angle true
  joint->arm[LEFT].arm_angle.target_angle.reach_target_angle = true;

	// right arm target angle true
  joint->arm[RIGHT].arm_angle.target_angle.reach_target_angle = true;

	// left arm PID reset
	PID_reset(&joint->arm[LEFT].traking_cs.arm_PID);

	// right arm PID reset
	PID_reset(&joint->arm[RIGHT].traking_cs.arm_PID);
}

/**
 * @details the function set target angle
 * @param[in] arm_driver - pointer to the structure of the elbow or shoulder (vertical/horizontal) drivers
 * @param[in] side - left or right side of hand
 * @param[in] target_angle - setpoint angle
 */
void acs_set_angle(float target_angle, arm_side_t side, arm_info_t *arm_driver)
{

  // setting the flag of reaching the specified angle to the value
	arm_driver[side].arm_angle.target_angle.reach_target_angle = false;

  // setting the target angle that we should reach
	arm_driver[side].arm_angle.target_angle.target_angle = target_angle;

}

/**
 * @details the function update current state of arm
 * @param[in] joint - pointer to the structure of the elbow or shoulder (vertical/horizontal) drivers
 * @param[in] side - left or right side of hand
 * @param[in] dt - function call period
 */
void acs_update_angle(float dt, arm_side_t side, joint_t *joint)
{
//  dbgprintf("1=%.4f\r\n", 5.0);

  // if we have already reached the specified angle, then we simply exit
  if(joint->arm[side].arm_angle.target_angle.reach_target_angle == true)
    return ;

  PID_t* PID = &joint->arm[side].traking_cs.arm_PID;

  float target_angle = joint->arm[side].arm_angle.target_angle.target_angle;
  float pwm_period = (float)joint->arm[side].traking_cs.control.pwm_period;
  float dead_zone = joint->arm[side].arm_angle.angle_dead_zone;

  float current_angle = acs_normalize_angle(&joint->arm[side].traking_cs,
                                            &joint->arm[side].arm_angle);

  // if less than zero, it means an error in the encoder readings
  if(current_angle < 0)
    return ;

  PID_err_calc(&PID->error, target_angle, current_angle);

  if(PID->error.P < 0)
    PID->error.P *= -1;

  float control = PID_out(PID, dt);

  if(control > pwm_period)
    control = pwm_period;

  if(side==LEFT)
  {
    if(current_angle < target_angle)
      joint->up(side, (uint16_t)control);
    else
      joint->down(side, (uint16_t)control);
  }
  else if(side==RIGHT)
  {
    if(current_angle < target_angle)
      joint->down(side, (uint16_t)control);
    else
      joint->up(side, (uint16_t)control);
  }

  // check deadzone of encoder
  if(PID->error.P <= dead_zone)
  {
    PID_reset(PID);
    joint->off(side);
    joint->arm[side].arm_angle.target_angle.reach_target_angle = true;
  }
}

// todo change acs_normalize_interval algorithm when calibration appears

/**
 * @details the function normalizes the angle interval
 * @param[in] arm_angle - pointer to the structure that contains info about angle (real min/max, normalize min/max)
 */
static void acs_normalize_interval (arm_angle_t* arm_angle)
{
  float min_angle = arm_angle->angle_lim.min_angle;
  float max_angle = arm_angle->angle_lim.max_angle;

  // example moving from 320 to 20
  // 320 - min_angle
  // 20 - max_angle
  if(min_angle>max_angle)
  {
    arm_angle->angle_norm_info.shift_from_zero = 360 - min_angle;
    arm_angle->angle_norm_lim.max_norm_angle = 360 - (min_angle-max_angle);
    arm_angle->angle_norm_info.zero_between_angle = true;
  }
  else
  {
	  arm_angle->angle_norm_lim.max_norm_angle = max_angle - min_angle;
    arm_angle->angle_norm_info.shift_from_zero = min_angle;
    arm_angle->angle_norm_info.zero_between_angle = false;
  }

  // minimum normalize angle always 0
  arm_angle->angle_norm_lim.min_norm_angle = 0;

}


/**
 * @details the function brings the current angle to the normalized angle change interval
 * @param[in] traking_cs - pointer to the structure of the tracking system of arm
 * @param[out] current_angle - current angle from normalized angle range
 */
static float acs_normalize_angle (traking_cs_t* traking_cs, arm_angle_t* arm_angle)
{

  float current_angle = encoder_read(&traking_cs->arm_encoder);

  // if less than zero, it means an error in the encoder readings
  if(current_angle < 0)
    return -1;

  // example moving from 10 to 350
  // in the process of moving, we cross 0
	if(arm_angle->angle_norm_info.zero_between_angle)
	{
		if(FROUND(current_angle+arm_angle->angle_norm_info.shift_from_zero)>=360)
			current_angle = current_angle - arm_angle->angle_lim.min_angle;

		else
			current_angle = current_angle + arm_angle->angle_norm_info.shift_from_zero;
	}
	else
		current_angle = current_angle - arm_angle->angle_norm_info.shift_from_zero;

	return FROUND(current_angle);

}




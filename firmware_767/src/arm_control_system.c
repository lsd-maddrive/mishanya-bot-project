#include <arm_control_system.h>

static void acs_normalize_interval (arm_angle_t* arm_angle);
static float acs_normalize_angle (traking_cs_t* traking_cs, arm_angle_t* arm_angle);

/**
 * @details the function brings the resulting angle into the normalized range
 * @param[in] arm_driver - pointer to the structure of the elbow or shoulder drivers
 */
void acs_init(arm_ctx_t* arm_driver)
{
	// left arm interval normalization
	acs_normalize_interval(&arm_driver->arm[LEFT].arm_angle);

	// right arm interval normalization
	acs_normalize_interval(&arm_driver->arm[RIGHT].arm_angle);

	// left arm target angle true
  arm_driver->arm[LEFT].arm_angle.target_angle.reach_target_angle = true;

	// right arm target angle true
  arm_driver->arm[RIGHT].arm_angle.target_angle.reach_target_angle = true;

	// left arm PID reset
	PID_reset(&arm_driver->arm[LEFT].traking_cs.arm_PID);

	// right arm PID reset
	PID_reset(&arm_driver->arm[RIGHT].traking_cs.arm_PID);
}

/**
 * @details the function set target angle
 * @param[in] arm_driver - pointer to the structure of the elbow or shoulder drivers
 * @param[in] side - left or right side of hand
 * @param[in] target_angle - setpoint angle
 */
void acs_set_angle(float target_angle, arm_side_t side, arm_info_t *arm_driver)
{
	arm_driver[side].arm_angle.target_angle.reach_target_angle = false;
	arm_driver[side].arm_angle.target_angle.target_angle = target_angle;

}

/**
 * @details the function update current state of arm
 * @param[in] arm_driver - pointer to the structure of the elbow or shoulder drivers
 * @param[in] side - left or right side of hand
 * @param[in] dt - function call period
 */
void acs_update_angle(float dt, arm_side_t side, arm_ctx_t *arm_driver)
{


  if(arm_driver->arm[side].arm_angle.target_angle.reach_target_angle == true)
    return ;

  PID_t* PID = &arm_driver->arm[side].traking_cs.arm_PID;

  float target_angle = arm_driver->arm[side].arm_angle.target_angle.target_angle;
  float pwm_period = (float)arm_driver->arm[side].traking_cs.control.pwm_period;
  float dead_zone = arm_driver->arm[side].arm_angle.angle_dead_zone;

  float current_angle = acs_normalize_angle(&arm_driver->arm[side].traking_cs,
                                            &arm_driver->arm[side].arm_angle);

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
      arm_driver->up(side, (uint16_t)control);
    else
      arm_driver->down(side, (uint16_t)control);

  }

  else if(side==RIGHT)
  {

    if(current_angle < target_angle)
      arm_driver->down(side, (uint16_t)control);

    else
      arm_driver->up(side, (uint16_t)control);

  }

  if(PID->error.P <= dead_zone)
  {
    PID_reset(PID);
    arm_off(side, arm_driver);
    arm_driver->arm[side].arm_angle.target_angle.reach_target_angle = true;
  }


}

/**
 * @details the function normalizes the angle interval
 * @param[in] traking_cs - pointer to the structure of the tracking system of arm
 */
static void acs_normalize_interval (arm_angle_t* arm_angle)
{
  float min_angle = arm_angle->angle_lim.min_angle;
  float max_angle = arm_angle->angle_lim.max_angle;

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

  if(current_angle < 0)
    return -1;

	if(arm_angle->angle_norm_info.zero_between_angle)
	{
		if((current_angle+arm_angle->angle_norm_info.shift_from_zero)>=360)
			current_angle = current_angle - arm_angle->angle_norm_lim.min_norm_angle;

		else
			current_angle = current_angle + arm_angle->angle_norm_info.shift_from_zero;
	}
	else
		current_angle = current_angle - arm_angle->angle_norm_info.shift_from_zero;

	return current_angle;

}




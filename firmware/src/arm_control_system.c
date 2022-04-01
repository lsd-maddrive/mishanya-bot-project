#include <arm_control_system.h>
#include "serial.h"

static void acs_normalize_interval (traking_cs_t* traking_cs);
static float acs_normalize_angle (traking_cs_t* traking_cs);

/**
 * @brief the function brings the resulting angle into the normalized range
 * @brief recieve the initial minimum angle and nirmalize struct
 * @return angle inside the normalized interval
 */
void acs_init(arm_driver_ctx_t* arm_driver)
{

  encoder_init(&arm_driver->arm[LEFT].traking_cs.arm_encoder);
  encoder_init(&arm_driver->arm[RIGHT].traking_cs.arm_encoder);

  acs_normalize_interval(&arm_driver->arm[LEFT].traking_cs);
  acs_normalize_interval(&arm_driver->arm[RIGHT].traking_cs);

  arm_driver->arm[LEFT].traking_cs.normalize_angle.target = true;
  arm_driver->arm[RIGHT].traking_cs.normalize_angle.target = true;

  PID_reset(&arm_driver->arm[LEFT].traking_cs.arm_PID);
  PID_reset(&arm_driver->arm[RIGHT].traking_cs.arm_PID);

}

/**
 * @brief the function set target angle ~(0-40)
 * @brief recieve target angle, the hand side and arm driver struct
 */
void acs_set_angle(float target_angle, arm_side_t side, arm_driver_ctx_t *arm_driver)
{
  arm_driver->arm[side].traking_cs.normalize_angle.target = 0;
  arm_driver->arm[side].traking_cs.normalize_angle.target_angle = target_angle;

}

/**
 * @brief the function update current state of arm
 * @brief recieve the function call period, the hand side and arm driver struct
 */
void acs_update_angle(float dt, arm_side_t side, arm_driver_ctx_t *arm_driver)
{

  if(arm_driver->arm[side].traking_cs.normalize_angle.target == 1)
    return ;

  PID_t* PID = &arm_driver->arm[side].traking_cs.arm_PID;

  float target_angle = arm_driver->arm[side].traking_cs.normalize_angle.target_angle;
  float pwm_period = (float)arm_driver->arm[side].control.pwm_setting_ctx.pwm_conf.period;
  float dead_zone = arm_driver->arm[side].traking_cs.angle_dead_zone;

  float current_angle = acs_normalize_angle(&arm_driver->arm[side].traking_cs);

  if(current_angle == -1)
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
    arm_driver->arm[side].traking_cs.normalize_angle.target = 1;
  }


}

/**
* @brief the function normalizes the angle interval
* @brief recieve the initial angles and nirmalize struct
*/
static void acs_normalize_interval (traking_cs_t* traking_cs)
{
  float min_angle = traking_cs->angle_lim.min_angle;
  float max_angle = traking_cs->angle_lim.max_angle;

  if(min_angle>max_angle)
  {

    traking_cs->normalize_angle.shift = 360 - min_angle;
    traking_cs->normalize_angle.max_norm_angle = 360 - (min_angle-max_angle);
    traking_cs->normalize_angle.zero_cross = true;

  }
  else
  {

    traking_cs->normalize_angle.max_norm_angle = max_angle - min_angle;
    traking_cs->normalize_angle.shift = min_angle;

  }

  traking_cs->normalize_angle.min_norm_angle = 0;

}


/**
 * @brief the function brings the resulting angle into the normalized range
 * @brief recieve the initial minimum angle and nirmalize struct
 * @return angle inside the normalized interval
 */
static float acs_normalize_angle (traking_cs_t* traking_cs)
{

  float current_angle = encoder_read(&traking_cs->arm_encoder);
  if(current_angle < 0)
    return -1;

	if(traking_cs->normalize_angle.zero_cross)
	{
		if((current_angle+traking_cs->normalize_angle.shift)>=360)
			current_angle = current_angle - traking_cs->angle_lim.min_angle;

		else
			current_angle = current_angle + traking_cs->normalize_angle.shift;
	}
	else
		current_angle = current_angle - traking_cs->normalize_angle.shift;

	return current_angle;

}




#include <arm_control_system.h>
#include "math.h"
/**
 * @details init arm control system 
 * @param[in] arm_driver - pointer to the structure of the elbow or shoulder (vertical/horizontal) drivers
 */
void acs_init(joint_t* joint)
{

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
void acs_set_angle(float target_angle, arm_side_t side, arm_info_t *arm_driver, angle_lim_t* global_angle_lim, float working_interval)
{

  float local_minimum = arm_driver[side].arm_angle.local_angle_lim.min_angle;
  float local_maximum = arm_driver[side].arm_angle.local_angle_lim.max_angle;
  float global_minimum = global_angle_lim->min_angle;

  // setting the flag of reaching the specified angle to the value
	arm_driver[side].arm_angle.target_angle.reach_target_angle = false;

    if(local_maximum > local_minimum && (local_maximum - local_minimum) > working_interval*1.1f)
    {
        float temp_target = local_minimum - (target_angle - global_minimum);
        arm_driver[side].arm_angle.target_angle.target_angle = temp_target > 0 ? temp_target : 360 + temp_target;
    }
    else if(local_maximum < local_minimum && (local_minimum - local_maximum) > working_interval*1.1f)
    {
        float temp_target = local_maximum - (target_angle - global_minimum);
        arm_driver[side].arm_angle.target_angle.target_angle = temp_target < local_maximum ? temp_target :
                                                                360 - (temp_target - local_maximum);
    }
    else if(local_maximum > local_minimum && (local_maximum - local_minimum) < working_interval*1.1f)
    {
        // setting the target angle that we should reach
        arm_driver[side].arm_angle.target_angle.target_angle = local_minimum + (target_angle - global_minimum);
    }
    else if(local_maximum < local_minimum && (local_minimum - local_maximum) < working_interval*1.1f)
    {
        // setting the target angle that we should reach
        arm_driver[side].arm_angle.target_angle.target_angle = local_minimum - (target_angle - global_minimum);
    }
}

/**
 * @details the function update current state of arm
 * @param[in] joint - pointer to the structure of the elbow or shoulder (vertical/horizontal) drivers
 * @param[in] side - left or right side of hand
 * @param[in] dt - function call period
 */
void acs_update_angle(float dt, arm_side_t side, joint_t *joint)
{

  // if we have already reached the specified angle, then we simply exit
  if(joint->arm[side].arm_angle.target_angle.reach_target_angle == true)
    return ;

  PID_t* PID = &joint->arm[side].traking_cs.arm_PID;

  float target_angle = joint->arm[side].arm_angle.target_angle.target_angle;
  float pwm_period = (float)joint->arm[side].traking_cs.control.pwm_period;
  float dead_zone = joint->arm[side].arm_angle.angle_dead_zone;

  float current_angle = encoder_read(&joint->arm[side].traking_cs.arm_encoder);

  // if less than zero, it means an error in the encoder readings
  if(current_angle < 0)
    return ;

  PID_err_circle_calc(&PID->error, target_angle, current_angle,
                      joint->working_interval,
                      joint->arm[side].arm_angle.local_angle_lim.min_angle,
                      joint->arm[side].arm_angle.local_angle_lim.max_angle);

  float control = PID_out(PID, dt, pwm_period);

    if(control > 0)
      joint->up(side, (uint16_t)(fabsf(control)));
    else
      joint->down(side, (uint16_t)(fabsf(control)));


  // check deadzone of encoder
  if(fabsf(PID->error.P) <= dead_zone)
  {
    PID_reset(PID);
    joint->off(side);
    joint->arm[side].arm_angle.target_angle.reach_target_angle = true;
  }
}





#include <close_sys_arm.h>

#define TIME_PREF 1/CH_CFG_ST_FREQUENCY

/**
 * @brief lowlevel function sets the specified angle
 * @brief recieve the hand side, the goal angle, PID struct and arm driver struct
 */
void close_sys_arm(float goal_angle, arm_side_t side, const arm_driver_ctx_t *arm_driver, PID_t *PID)
{

  PID_reset(PID);

	normalize_angle_t arm_angle = {
		.max_norm_angle = 0,
		.min_norm_angle = 0,
		.shift = 0,
		.zero_cross = false
	};

	virtual_timer_t encoder_timer;


  float pwm_period = arm_driver->arm[side].control.pwm_setting_ctx.pwm_conf.period;
  float dead_zone = arm_driver->arm[side].close_conf.angle_dead_zone;
  float dt = arm_driver->arm[side].close_conf.dt;
  float min_angle = arm_driver->arm[side].close_conf.angle_lim.min_angle;
  float max_angle = arm_driver->arm[side].close_conf.angle_lim.max_angle;

	float prev_time = 0;
	float current_angle = 0;
	float period = 0;
	float delta_t = 0;

	chVTObjectInit(&encoder_timer);

	// convert the angle range so that it starts from zero
	normalize_interval(min_angle, max_angle, &arm_angle);

	prev_time = chVTGetSystemTime();

	while(1)
	{
		// bring the angle into the normalized range
		current_angle = normalize_angle(min_angle, &arm_angle);

    PID_err_calc(&PID->error, goal_angle, current_angle);

    if(PID->error.P < 0)
      PID->error.P *= -1;

		delta_t = chVTGetSystemTime()-prev_time;

		if(delta_t >= dt)
		{

			prev_time = chVTGetSystemTime();
			period = PID_out(PID, delta_t*TIME_PREF);

			if(period > pwm_period)
				period = pwm_period;

		}

		if(side==LEFT)
		{

			if(current_angle<goal_angle)
				arm_driver->down(side, (uint16_t)period);

			else
				arm_driver->up(side, (uint16_t)period);

		}
		else if(side==RIGHT)
		{

			if(current_angle<goal_angle)
				arm_driver->up(side, (uint16_t)period);

			else
				arm_driver->down(side, (uint16_t)period);

		}

		if(PID->error.P <= dead_zone) break;

	}

	arm_driver->off(side);
	chVTDoResetI (&encoder_timer);

}

/**
 * @brief the function normalizes the angle interval
 * @brief recieve the initial angles and nirmalize struct
 */
void normalize_interval (float min_angle, float max_angle, normalize_angle_t *arm_angle)
{

		if(min_angle>max_angle)
		{

			arm_angle->shift = 360 - min_angle;
			arm_angle->max_norm_angle = 360 - (min_angle-max_angle);
			arm_angle->zero_cross = true;

		}
		else
		{

			arm_angle->max_norm_angle = max_angle - min_angle;
			arm_angle->shift = min_angle;

		}

		arm_angle->min_norm_angle = 0;

}

/**
 * @brief the function brings the resulting angle into the normalized range
 * @brief recieve the initial minimum angle and nirmalize struct
 * @return angle inside the normalized interval
 */
double normalize_angle (float min_angle, normalize_angle_t *arm_angle)
{

	double current_angle = Encoder_Read();

	if(arm_angle->zero_cross)
	{
		if((current_angle+arm_angle->shift)>=360)
			current_angle = current_angle - min_angle;

		else
			current_angle = current_angle + arm_angle->shift;
	}
	else
		current_angle = current_angle - arm_angle->shift;

	return current_angle;

}

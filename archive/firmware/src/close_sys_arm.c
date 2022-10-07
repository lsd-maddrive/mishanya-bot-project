#include <close_sys_arm.h>

#define TIME_PREF 1/CH_CFG_ST_FREQUENCY


typedef struct normalize_angle{
    float	max_norm_angle;
    float	min_norm_angle;
    float	shift;
    bool	zero_cross;
}normalize_angle_t;


static double normalize_angle (float min_angle, normalize_angle_t *arm_angle);
static void normalize_interval (float min_angle, float max_angle, normalize_angle_t *arm_angle);
static void error_calculate (error_type_t *err_reg, float angle, float current_angle);



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

  float pwm_period = arm_driver->arm[side].control.arm_ctx.pwm_conf.period;
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

		error_calculate(&PID->error, goal_angle, current_angle);

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
				arm_driver->down(side, period);

			else
				arm_driver->up(side, period);

		}
		else if(side==RIGHT)
		{

			if(current_angle<goal_angle)
				arm_driver->up(side, period);

			else
				arm_driver->down(side, period);

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
static void normalize_interval (float min_angle, float max_angle, normalize_angle_t *arm_angle)
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
static double normalize_angle (float min_angle, normalize_angle_t *arm_angle)
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

/**
 * @brief error calculation function
 * @brief recieve the goal angle, current angle and error struct
 */
static void error_calculate (error_type_t *err_reg, float angle, float current_angle)
{

	err_reg->P = angle-current_angle;

	if(err_reg->P<0)
		err_reg->P *=-1;

}
#include <close_sys_arm.h>

#define DEAD_ZONE 1

#define TIME_PREF 1/CH_CFG_ST_FREQUENCY

#define dt 100

static virtual_timer_t encoder;

void close_sys_arm(float goal_angle, arm_side_t side, const arm_driver_ctx_t *arm_driver, PID_t *PID)
{
	PID->error.D = 0;
	PID->error.I = 0;
	PID->error.P = 0;
	PID->error.prev_P = 0;

	control_driver_t control = arm_driver->arm[side];

	normalize_angle_t arm_angle = {
			.max_norm_angle = 0,
			.min_norm_angle = 0,
			.min_norm_angle = 0,
			.zero_cross = false
	};

	float prev_time = 0;
	float current_angle = 0;
	float period = 0;
	float delta_t = 0;


	chVTObjectInit(&encoder);

	normalize_interval(control->angle_lim.min_angle, control->angle_lim.max_angle, &arm_angle);

	prev_time = chVTGetSystemTime();


	while(1)
	{
		current_angle = normalize_angle(control->angle_lim.min_angle, &arm_angle);

		error_calculate (&PID->error, goal_angle, current_angle);

		delta_t = chVTGetSystemTime()-prev_time;

		if(delta_t>=dt)
		{

			prev_time = chVTGetSystemTime();
			period = PID_out(&PID, delta_t*TIME_PREF);

			if(period > ARM_PERIOD)
				period = ARM_PERIOD;

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

		if(PID->error.P<=DEAD_ZONE) break;

	}

	arm_driver->off(side);
	chVTDoResetI (&encoder);

}


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

void error_calculate (error_type_t *err_reg, float angle, float current_angle)
{

	err_reg->P = angle-current_angle;

	if(err_reg->P<0)
		err_reg->P *=-1;

}



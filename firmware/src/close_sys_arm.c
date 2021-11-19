#include <close_sys_arm.h>

#define dead_zone 0.5

#define time_pref 1/CH_CFG_ST_FREQUENCY

#define dt 100

static virtual_timer_t encoder;

PID_t ARM_PID = {580, 80, 0};

float min_angle_left = 334.9511;

float max_angle_left = 18.2812;

float min_angle_right = 0;

float max_angle_right = 0;

void close_sys_arm(float goal_angle, arm_t ARM)
{
	float prev_time = 0;
	error_type_t error = {0, 0, 0, 0};
	normalize_angle_t arm_angle = {0, 0, 0, false};
	close_sys_t arm = {0, 0, 0, 0};
	lim_angle_t lim_angle = {0, 0};

	chVTObjectInit(&encoder);

	if(ARM==RIGHT_ARM)
	{

		lim_angle.min_angle = min_angle_right;
		lim_angle.max_angle = max_angle_right;

	}

	if(ARM==LEFT_ARM)
	{

		lim_angle.min_angle = min_angle_left;
		lim_angle.max_angle = max_angle_left;

	}

	normalize_interval (lim_angle.min_angle, lim_angle.max_angle, &arm_angle);

	prev_time = chVTGetSystemTime();



	while(1)
	{
		arm.current_angle = normalize_angle (lim_angle.min_angle, &arm_angle);

		error_calculate (&error, goal_angle, arm.current_angle);

		arm.delta_t = chVTGetSystemTime()-prev_time;
		if(arm.delta_t>=dt)
		{

			prev_time = chVTGetSystemTime();
			arm.period = PID_out(&error, ARM_PID, arm.delta_t*time_pref);

		}

		if(ARM==LEFT_ARM)
		{

			if(arm.current_angle<goal_angle)
				{

					ARM_down(ARM, arm.period);

				}

			else

				{

					ARM_up(ARM, arm.period);

				}

		}

		if(ARM==RIGHT_ARM)
		{

			if(arm.current_angle<goal_angle)
				{

					ARM_up(ARM, arm.period);

				}

			else

				{

					ARM_down(ARM, arm.period);

				}

		}

		arm.ref_error = 100*error.P/goal_angle;

		if(arm.ref_error<=dead_zone)
		{

			break;

		}


	}

	Off_ARM(ARM);

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
		{

			current_angle = current_angle - min_angle;

		}

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

	if(err_reg->P>17)
	{

		err_reg->P = 17;

	}

}



#include <close_sys_arm.h>


#define down_period 3000

#define dead_zone 0.5

#define time_pref 0.00001

#define dt 100

static virtual_timer_t encoder;

struct PID ARM_PID = {580, 80, 0};


void close_left_arm(double goal_angle)
{
	struct error_type error = {0, 0, 0, 0};
	struct normalize_angle left_arm_angle = {0, 0, 0, false};

	chVTObjectInit(&encoder);

	double min_left = 334.9511;
    double max_left = 18.2812;

	double current_angle_left = 0;
	double period = 0;

	double ref_error = 0;


	double prev_time = 0;


	double delta_t = 0;


	normalize_interval (min_left, max_left, &left_arm_angle);

	prev_time = chVTGetSystemTime();



	while(1)
	{
		current_angle_left = normalize_angle (min_left, &left_arm_angle);

		error_calculate (&error, goal_angle, current_angle_left);

		delta_t = chVTGetSystemTime()-prev_time;
		if(delta_t>=dt)
		{
			prev_time = chVTGetSystemTime();
			period = PID_out(&error, ARM_PID, delta_t*time_pref);
		}


		if(current_angle_left<goal_angle)
		{
			ARM_down(LEFT_ARM, period);
		}
		else
		{
			ARM_up(LEFT_ARM, period);
		}

		dbgprintf("%.4f\r\n", current_angle_left);

		ref_error = 100*error.P/goal_angle;

		if(ref_error<=dead_zone)
		{
			break;
		}

	}
	Off_ARM(LEFT_ARM);


}

void normalize_interval (double min_angle, double max_angle, normalize_angle_t *arm_angle)
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

double normalize_angle (double min_angle, normalize_angle_t *arm_angle)
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

void error_calculate (error_type_t *err_reg, double angle, double current_angle)
{
	err_reg->P = angle-current_angle;

	if(err_reg->P<0)
		err_reg->P *=-1;

	if(err_reg->P>17)
	{
		err_reg->P = 17;
	}

}



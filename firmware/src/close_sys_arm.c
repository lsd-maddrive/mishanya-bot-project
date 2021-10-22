#include <close_sys_arm.h>


#define delta_max 1.05
#define delta_min 0.95
#define up_period 1000
#define down_period 1000

void close_right_arm(double angle)
{
	double current_angle = Encoder_Read();
	while(current_angle<angle*delta_min || current_angle>angle*delta_max)
	{
		if(current_angle>angle)
		{
			ARM_up(RIGHT_ARM, up_period);
		}
		else
		{
			ARM_down(RIGHT_ARM, down_period);
		}
		current_angle = Encoder_Read();
		dbgprintf("%.4f\r\n", current_angle);
	}
	Off_ARM(RIGHT_ARM);
}

void close_left_arm(double angle)
{
	double current_angle = Encoder_Read();
	while(current_angle<angle*delta_min || current_angle>angle*delta_max)
	{
		if(current_angle>angle)
		{
			ARM_down(LEFT_ARM, down_period);
		}
		else
		{
			ARM_up(LEFT_ARM, up_period);
		}
		current_angle = Encoder_Read();
	}
	Off_ARM(LEFT_ARM);
}




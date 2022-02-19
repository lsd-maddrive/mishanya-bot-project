#ifndef INCLUDE_CLOSE_ARM_SYS__H
#define INCLUDE_CLOSE_ARM_SYS__H

#include <common.h>
#include <encoder.h>
#include <arm_driver.h>
#include <serial.h>
#include <PID.h>
#include <stdbool.h>

typedef struct normalize_angle{
	float	max_norm_angle;
	float	min_norm_angle;
	float	shift;
	bool	zero_cross;
}normalize_angle_t;

void close_sys_arm(float goal_angle, arm_side_t side, const arm_driver_ctx_t *arm_driver, PID_t *PID);


#endif

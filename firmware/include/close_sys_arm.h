#ifndef INCLUDE_CLOSE_ARM_SYS__H
#define INCLUDE_CLOSE_ARM_SYS__H

#include <common.h>
#include <encoder.h>
#include <arm_driver.h>
#include <serial.h>
#include <PID.h>
#include <stdbool.h>

typedef struct normalize_angle{
    float  max_norm_angle;
    float  min_norm_angle;
    float  shift;
    bool 	zero_cross;
}normalize_angle_t;

typedef struct lim_angle{
    float  max_angle;
    float  min_angle;
}lim_angle_t;

typedef struct close_sys{
    float  current_angle;
    float  period;
    float  delta_t;
}close_sys_t;


void close_sys_arm(float goal_angle, arm_t ARM);

void normalize_interval (float min_angle, float max_angle, normalize_angle_t *arm_angle);

double normalize_angle (float min_angle, normalize_angle_t *arm_angle);

void error_calculate (error_type_t *err_reg, float angle, float current_angle);

#endif

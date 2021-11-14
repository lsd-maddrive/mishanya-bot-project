#ifndef INCLUDE_CLOSE_ARM_SYS__H
#define INCLUDE_CLOSE_ARM_SYS__H

#include <common.h>
#include <encoder.h>
#include <arm_driver.h>
#include <serial.h>
#include <PID.h>
#include <stdbool.h>

typedef struct normalize_angle{
    double  max_norm_angle;
    double  min_norm_angle;
    double  shift;
    bool 	zero_cross;
}normalize_angle_t;

//void close_right_arm(double angle);

void close_left_arm(double goal_angle);

void normalize_interval (double min_angle, double max_angle, normalize_angle_t *arm_angle);

double normalize_angle (double min_angle, normalize_angle_t *arm_angle);

void error_calculate (error_type_t *err_reg, double angle, double current_angle);

#endif

#ifndef PID__H
#define PID__H

#include "common.h"

typedef struct{
    float  kp;         // the value of the P coefficient
    float  ki;         // the value of the I coefficient
    float  kd;         // the value of the D coefficient
}coef_t;

typedef struct{
    float  P;          // P component
    float  prev_P;     // prev P component
    float  I;          // I component
    float  D;          // D component
}error_type_t;

typedef struct{
    error_type_t error;
    coef_t coef;
}PID_t;

float PID_out(PID_t* reg, float dt, float saturation);
void PID_reset(PID_t* reg);
void PID_err_calc(error_type_t *err_reg, float angle, float current_angle);
void PID_set_coef(PID_t* reg, float kp, float kd, float ki);
void PID_err_circle_calc(error_type_t *err_reg, float setpoint, float current_point, float working_interval, float min, float max);

#endif

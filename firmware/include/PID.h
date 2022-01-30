#ifndef PID__H
#define PID__H

#include <common.h>


typedef struct{
    double  kp;
    double  ki;
    double  kd;
}coef_t;

typedef struct{
    double  P;
    double  prev_P;
    double  I;
    double  D;
}error_type_t;

typedef struct{
	error_type_t error;
	coef_t coef;
}PID_t;

double PID_out(PID_t* reg, double dt);

#endif

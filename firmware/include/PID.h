#ifndef PID__H
#define PID__H

#include <common.h>


typedef struct PID{
    double  kp;
    double  ki;
    double  kd;
}PID_t;

typedef struct error_type{
    double  P;
    double  prev_P;
    double  I;
    double  D;
}error_type_t;


double PID_out(error_type_t *err_reg, PID_t coef_reg, double dt);

#endif

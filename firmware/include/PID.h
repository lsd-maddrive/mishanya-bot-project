#ifndef PID__H
#define PID__H

#include <common.h>

/**
 * @brief struct coef PID 
 */
typedef struct PID{
    double  kp;
    double  ki;
    double  kd;
}PID_t;

/**
 * @brief struct error PID 
 */
typedef struct error_type{
    double  P;
    double  prev_P;
    double  I;
    double  D;
}error_type_t;

/**
 * @brief PID 
 * @return return PID value
 */
double PID_out(error_type_t *err_reg, PID_t coef_reg, double dt);

#endif

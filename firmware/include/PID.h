#ifndef PID__H
#define PID__H

#include <common.h>



typedef struct{
  double  kp;         // the value of the P coefficient
  double  ki;         // the value of the I coefficient
  double  kd;         // the value of the D coefficient
}coef_t;

typedef struct{
  double  P;          // P component
  double  prev_P;     // prev P component
  double  I;          // I component
  double  D;          // D component
}error_type_t;

typedef struct{
	error_type_t error;
	coef_t coef;
}PID_t;

double PID_out(PID_t* reg, double dt);
void PID_reset(PID_t* reg);

#endif

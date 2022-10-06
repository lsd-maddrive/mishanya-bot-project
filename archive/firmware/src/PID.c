#include <PID.h>

/**
 * @brief PID function
 * @brief recieve time step and PID struct
 */
double PID_out(PID_t* reg, double dt)
{

	double control = 0;

	reg->error.I += reg->error.P*dt;
	reg->error.D = (reg->error.P - reg->error.prev_P)/dt;
	reg->error.prev_P = reg->error.P;
	control = reg->error.P*reg->coef.kp + reg->error.I*reg->coef.ki + reg->error.D*reg->coef.kd;

	return control;

}

/**
 * @brief PID coefficients reset
 * @brief recieve time PID struct
 */
void PID_reset(PID_t* reg)
{

  // reset the error coefficients of the regulator
  reg->error.D = 0;
  reg->error.I = 0;
  reg->error.P = 0;
  reg->error.prev_P = 0;

}

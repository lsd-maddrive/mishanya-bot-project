#include "PID.h"

/**
 * @details calculates the control of the pid controller
 * @param[in] reg - pointer to the PID structure
 * @param[in] dt - time step
 * @param[out] control - control signal
 */
float PID_out(PID_t* reg, float dt)
{

  float control = 0;

	reg->error.I += reg->error.P*dt;
	reg->error.D = (reg->error.P - reg->error.prev_P)/dt;
	reg->error.prev_P = reg->error.P;
	control = reg->error.P*reg->coef.kp + reg->error.I*reg->coef.ki + reg->error.D*reg->coef.kd;

	return control;

}

/**
 * @details reset PID controller coefficients
 * @param[in] reg - pointer to the PID structure
 */
void PID_reset(PID_t* reg)
{

  // reset the error coefficients of the regulator
  reg->error.D = 0;
  reg->error.I = 0;
  reg->error.P = 0;
  reg->error.prev_P = 0;

}

/**
 * @brief error calculation function
 * @param[in] err_reg - pointer to the error PID structure
 * @param[in] setpoint - desired value of the controlled variable
 * @param[in] current_point - current value of the controlled variable
 */
void PID_err_calc (error_type_t *err_reg, float setpoint, float current_point)
{

  err_reg->P = setpoint-current_point;

}
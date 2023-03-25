#include "PID.h"
#include "math.h"

/**
 * @brief PID function
 * @brief recieve time step and PID struct
 */
float PID_out(PID_t* reg, float dt, float saturation)
{

  float control = 0;

	reg->error.I += reg->error.P*dt;
	reg->error.D = (reg->error.P - reg->error.prev_P)/dt;
	reg->error.prev_P = reg->error.P;
	control = reg->error.P*reg->coef.kp + reg->error.I*reg->coef.ki + reg->error.D*reg->coef.kd;

  if(control > saturation)
  {
    return saturation;
  }
  if(control < saturation)
  {
    return -saturation;
  }

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


/**
 * @brief error calculation function
 * @brief recieve the setpoint, current point and error struct
 */
void PID_err_calc (error_type_t *err_reg, float setpoint, float current_point)
{
  err_reg->P = setpoint-current_point;

}

/**
 * @brief error calculation function when working on a circle
 * @brief recieve the setpoint, current point and error struct
 */
void PID_err_circle_calc (error_type_t *err_reg, float setpoint, float current_point, float working_interval, float min, float max)
{
    float diff = 0;

    if((min < max) && ((max - min) < working_interval*1.1f))
    {
        err_reg->P = setpoint-current_point;

        return;
    }
    else if((max < min) && ((min - max) < working_interval*1.1f))
    {
        err_reg->P = current_point - setpoint;

        return;
    }
    else if((min < max) && ((max - min) > working_interval*1.1f))
    {
        diff = 360 - max;
    }
    else if((max < min) && ((min - max) > working_interval*1.1f))
    {
        diff = 360 - min;
    }

    setpoint = (setpoint + diff) < 360 ? (setpoint + diff) : (setpoint + diff) - 360;
    current_point = (current_point + diff) < 360 ? (current_point + diff) : (current_point + diff) - 360;

    if(min < max)
    {
        err_reg->P = current_point - setpoint;
        return;
    }

    err_reg->P = setpoint - current_point;


}

/**
 * @brief PID coefficients set
 * @param[in] reg - pointer to pid regulator
 * @param[in] kp - proportional coef
 * @param[in] kd - differential coef
 * @param[in] ki - integral coef
 */
void PID_set_coef(PID_t* reg, float kp, float kd, float ki)
{
  reg->coef.kp = kp;
  reg->coef.ki = ki;
  reg->coef.kd = kd;

}

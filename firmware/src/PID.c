#include <PID.h>


/**
 * @brief PID 
 * @return return PID value
 */
double PID_out(error_type_t *err_reg, PID_t coef_reg, double dt)
{
	
    double control=0;
    err_reg->I += err_reg->P*dt;
    err_reg->D = (err_reg->P - err_reg->prev_P)/dt;
    err_reg->prev_P = err_reg->P;
    control = err_reg->P*coef_reg.kp + err_reg->I*coef_reg.ki + err_reg->D*coef_reg.kd;

    return control;

}

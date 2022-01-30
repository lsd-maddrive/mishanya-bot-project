#include <PID.h>

double PID_out(PID_t reg, double dt)
{

	double control=0;

	reg->error.I += reg->error.P*dt;
	reg->error.D = (reg->error.P - reg->error.prev_P)/dt;
	reg->error.prev_P = reg->error.P;
	control = reg->error.P*reg->coef.kp + reg->error.I*reg->coef.ki + reg->error.D*reg->coef.kd;

	return control;

}

#ifndef INCLUDE_LLD_RED_DRIVER_H
#define INCLUDE_LLD_RED_DRIVER_H

#include "common.h"
#include "lld_bridge_system.h"

/************ Driver with one channel PWM ************/

void lld_red_init_driver(control_driver_t* driver, PWMDriver* pwm_ptr, uint8_t ch_num);
void lld_red_driver_direct(control_driver_t* driver, float period);
void lld_red_driver_reverse(control_driver_t* driver, float period);
void lld_red_driver_off(control_driver_t* driver);



#endif

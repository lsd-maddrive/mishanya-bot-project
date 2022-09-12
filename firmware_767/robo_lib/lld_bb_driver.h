#ifndef INCLUDE_LLD_BB_DRIVER_H
#define INCLUDE_LLD_BB_DRIVER_H

#include "common.h"
#include "lld_bridge_system.h"

/************ Driver with complementary mode ************/

void lld_bb_init_driver(control_driver_t* driver, PWMDriver* pwm_ptr_left_shoulder, uint8_t ch_num_left,
		PWMDriver* pwm_ptr_right_shoulder, uint8_t ch_num_right);
void lld_bb_driver_direct(control_driver_t* driver, float period);
void lld_bb_driver_reverse(control_driver_t* driver, float period);
void lld_bb_driver_off(control_driver_t* driver);

#endif

#ifndef INCLUDE_MOTOR_H
#define INCLUDE_MOTOR_H

#include "common.h"
#include "lld_bb_driver.h"
#include "lld_bridge_system.h"
#include "cnfg_peripherals.h"

typedef enum{MOTOR_1, MOTOR_2, MOTOR_3}type_motor;

void lld_motor_init(type_motor motor_n);
void lld_motor(type_motor motor_n, float duty_cycle);
#endif

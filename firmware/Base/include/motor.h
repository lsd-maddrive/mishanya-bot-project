#ifndef INCLUDE_MOTOR_H
#define INCLUDE_MOTOR_H

#include "common.h"
#include "lld_bb_driver.h"
#include "lld_bridge_system.h"
#include "cnfg_peripherals.h"

typedef enum {MOTOR_1, MOTOR_2, MOTOR_3} type_motor;

/**
 * @brief Init peripheral and pwm for control motor
 * @args motor_n is value from enum
 */
void lldMotorInit(type_motor motor_n);

/**
 * @brief Set type motor and pwm duty cycle for control
 * @args motor_n is value from enum, duty cycle pwm for control motor, flag percent: 1 - percent value, 0 - raw value
 */
void lldSetMotorPower(type_motor motor_n, float duty_cycle, int8_t flag_percent);
#endif

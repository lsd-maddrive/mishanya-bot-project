#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

#include "ch.h"
#include "hal.h"
#include "chprintf.h"



#define PROGRAM_MASTER 0
/***    SERVO FOR HAND       ***/
#define PROGRAM_TEST_SERVO_HAND 1
/***    SERVO FOR WRIST       ***/
#define PROGRAM_TEST_SERVO_WRIST 2

#define MAIN_PROGRAM PROGRAM_TEST_SERVO_HAND

/**
 * @brief Overflow protection
 * @args duty_cycle is varible to be checked
 * @args low is minimum value
 * @args high is maximum value
 * @return duty_cycle
 */
int32_t Check(int32_t duty_cycle, int32_t low,int32_t high);

#endif

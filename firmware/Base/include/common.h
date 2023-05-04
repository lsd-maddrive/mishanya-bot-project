#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "ch.h"
#include "hal.h"
#include "chprintf.h"


#define PROGRAM_MASTER 0

#define PROGRAM_TEST_ENCODER_BASE_ALL    1
#define PROGRAM_TEST_ENCODER_BASE_1      2
#define PROGRAM_TEST_ENCODER_BASE_2      3
#define PROGRAM_TEST_ENCODER_BASE_3      4
#define PROGRAM_TEST_ODOMETRY_BASE_ENC_1 5
#define PROGRAM_TEST_ODOMETRY_BASE_ENC_2 6
#define PROGRAM_TEST_ODOMETRY_BASE_ENC_3 7
#define PROGRAM_TEST_ODOMETRY_BASE_ALL   8
#define PROGRAM_TEST_MOTOR_1             9
#define PROGRAM_TEST_MOTOR_2             10
#define PROGRAM_TEST_MOTOR_3             11
#define PROGRAM_TEST_MOTOR_ALL           12
#define PROGRAM_TEST_MOTOR_PER_1         13
#define PROGRAM_TEST_MOTOR_PER_2         14
#define PROGRAM_TEST_MOTOR_PER_3         15
#define PROGRAM_TEST_MOTOR_PER_ALL       16
#define PROGRAM_TEST_SPEED_FILTER_GRAPHS 17
#define PROGRAM_TEST_CLOSED_SYSTEM_DRIVE 18
#define PROGRAM_TEST_I2C                 19
#define PROGRAM_TEST_GYROSCOPE           20
#define PROGRAM_TEST_KINEMATICS          21
#define PROGRAM_TEST_JOYSTICK            22

#define MAIN_PROGRAM PROGRAM_TEST_JOYSTICK

/*============================================================================*/
/* MACROS     Overflow protection                                             */
/*============================================================================*/
#define CLIP_VALUE(x, min, max) ((x) < (min) ? (min) :      \
                                 (x) > (max) ? (max) : (x))

/*============================================================================*/
/* MACROS     Parameters Robot                                                */
/*============================================================================*/
//radius base
#define L (float)0.406
//radius wheel
#define R (float)0.061
// Wheel arrangement degrees
//#define THETA_1 (float)(M_PI/3)
//#define THETA_2 (float)(M_PI/6)
#define THETA (float)(M_PI/3)

/*============================================================================*/
/* MACROS     MATH                                                            */
/*============================================================================*/

#define GRAD_TO_RAD (float)(M_PI/180)
#define RAD_TO_REVS (float)(1/(2 * M_PI))

#endif

#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "stdint.h"
#include "low_level.h"

#define ARM_QTY 2U
#define DEGREE_OF_FREEDOM_QTY 3U

typedef enum {
    LEFT = 0,
    RIGHT = 1,
    NONE_SIDE = 2
} arm_side_t;

#define PROGRAM_MASTER 0
#define PROGRAM_TEST_SERVO_LEFT_HAND 1
#define PROGRAM_TEST_SERVO_LEFT_WRIST 2
#define PROGRAM_TEST_SERVO_RIGHT_HAND 3
#define PROGRAM_TEST_SERVO_RIGHT_WRIST 4
#define PROGRAM_TEST_SERVO_NONLINEAR 5
#define PROGRAM_TEST_PID 6
#define PROGRAM_TEST_ARM_ENCODER 7
#define PROGRAM_TEST_ARM_HIGH_FUNCTION 8
#define PROGRAM_TEST_ARM_CONTROL_SYSTEM 9
#define PROGRAM_TEST_ARM_KINEMATIC 10
#define MAIN_PROGRAM PROGRAM_MASTER

/*============================================================================*/
/* MACROS     Overflow protection                                             */
/*============================================================================*/
#define CLIP_VALUE(x, min, max) ((x) < (min) ? (min) :      \
                                 (x) > (max) ? (max) : (x))


#endif

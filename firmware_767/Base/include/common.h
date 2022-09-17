#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "stdint.h"
#include "math.h"

#define PROGRAM_MASTER 0

#define PROGRAM_TEST_ENCODER_BASE_ALL 1
#define PROGRAM_TEST_ENCODER_BASE_1 2
#define PROGRAM_TEST_ENCODER_BASE_2 3
#define PROGRAM_TEST_ENCODER_BASE_3 4
#define PROGRAM_TEST_ODOMETRY_BASE_ENC_1 5
#define PROGRAM_TEST_ODOMETRY_BASE_ENC_2 6
#define PROGRAM_TEST_ODOMETRY_BASE_ENC_3 7
#define PROGRAM_TEST_ODOMETRY_BASE_ALL 8

#define MAIN_PROGRAM PROGRAM_TEST_ODOMETRY_BASE_ALL

/*============================================================================*/
/* MACROS     Overflow protection                                             */
/*============================================================================*/
#define CLIP_VALUE(x, min, max) ((x) < (min) ? (min) :      \
                                 (x) > (max) ? (max) : (x))

#endif

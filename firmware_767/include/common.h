#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#define PROGRAM_MASTER 0

#define PROGRAM_TEST_SERVO_LEFT_HAND 1

#define MAIN_PROGRAM PROGRAM_TEST_SERVO_LEFT_HAND

/*============================================================================*/
/* MACROS     Overflow protection                                             */
/*============================================================================*/
#define CLIP_VALUE(x, min, max) ((x) < (min) ? (min) :      \
                                 (x) > (max) ? (max) : (x))

#endif

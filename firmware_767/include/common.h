#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "stdint.h"

#define PROGRAM_MASTER 0

#define PROGRAM_TEST_SERVO 1

#define MAIN_PROGRAM PROGRAM_TEST_SERVO

/*============================================================================*/
/* MACROS     Overflow protection                                             */
/*============================================================================*/
#define CLIP_VALUE(x, min, max) ((x) < (min) ? (min) :      \
                                 (x) > (max) ? (max) : (x))

typedef enum {LEFT_HAND,LEFT_WRIST,RIGHT_HAND,RIGHT_WRIST}type_servo;

#endif

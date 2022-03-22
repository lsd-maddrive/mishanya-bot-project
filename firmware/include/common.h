#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "stdbool.h"


#define PROGRAM_MASTER 0

#define PROGRAM_TEST_ENCODER 1

#define PROGRAM_TEST_ELBOW_DRIVER 2

#define PROGRAM_TEST_NORMALIZE 3

#define PROGRAM_TEST_PID 4

#define PROGRAM_TEST_ARM_CLOSE_SYS 5

#define MAIN_PROGRAM PROGRAM_TEST_ARM_CLOSE_SYS



#endif

#ifndef INCLUDE_ARM_DRIVER_H
#define INCLUDE_ARM_DRIVER_H

#include <common.h>

#define PWM1_frequency	500000
#define PWM1_period		10000


typedef enum {
	LEFT_ARM,
	RIGHT_ARM
} arm_t;

/**
 * @brief   Initialize arm driver
 */
void ARM_DRIVER_init(void);

/**
 * @brief recieve the hand number and the filling period
 * the function controls the raising of the hand up
 */
void ARM_up(arm_t ARM, uint16_t PWM_period);

/**
 * @brief recieve the hand number and the filling period
 * the function controls the raising of the hand down
 */
void ARM_down(arm_t ARM, uint16_t PWM_period);

/**
 * @brief recieve the hand number
 * the function disables the selected hand
 */
void Off_ARM (arm_t ARM);

#endif

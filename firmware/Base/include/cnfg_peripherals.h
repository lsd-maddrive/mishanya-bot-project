#ifndef INCLUDE_CNFG_PERIPHERALS_H
#define INCLUDE_CNFG_PERIPHERALS_H

#include "common.h"

// *******************pwm config******************* //
#define PWM_FREQUENCY 1000000
#define PWM_PERIOD 1000

// *******************Motor1******************* //

//pins
#define MOTOR1_PWM_HIN1 PAL_LINE(GPIOE, 11)
#define MOTOR1_PWM_LIN1 PAL_LINE(GPIOE, 10)
#define MOTOR1_PWM_HIN2 PAL_LINE(GPIOE, 13)
#define MOTOR1_PWM_LIN2 PAL_LINE(GPIOE, 12)

//channels
#define M1_CH_H1L1 1
#define M1_CH_H2L2 2

//alternating functions
#define M1_AF_H1L1 PAL_MODE_ALTERNATE(1)
#define M1_AF_H2L2 PAL_MODE_ALTERNATE(1)

// *******************Motor2******************* //

//pins
#define MOTOR2_PWM_HIN1 PAL_LINE(GPIOC, 6)
#define MOTOR2_PWM_LIN1 PAL_LINE(GPIOA, 5)
#define MOTOR2_PWM_HIN2 PAL_LINE(GPIOC, 7)
#define MOTOR2_PWM_LIN2 PAL_LINE(GPIOB, 0)

//channels
#define M2_CH_H1L1 0
#define M2_CH_H2L2 1

//alternating functions
#define M2_AF_H1L1 PAL_MODE_ALTERNATE(3)
#define M2_AF_H2L2 PAL_MODE_ALTERNATE(3)

// *******************Motor3******************* //

//pins
#define MOTOR3_PWM_HIN1 PAL_LINE(GPIOC, 8)
#define MOTOR3_PWM_LIN1 PAL_LINE(GPIOB, 1)
#define MOTOR3_PWM_HIN2 PAL_LINE(GPIOE, 9)
#define MOTOR3_PWM_LIN2 PAL_LINE(GPIOE, 8)

//channels
#define M3_CH_H1L1 2
#define M3_CH_H2L2 0

//alternating functions
#define M3_AF_H1L1 PAL_MODE_ALTERNATE(3)
#define M3_AF_H2L2 PAL_MODE_ALTERNATE(1)

/**
 * @brief Init peripherals
 */
void cnfgInit(void);

#endif

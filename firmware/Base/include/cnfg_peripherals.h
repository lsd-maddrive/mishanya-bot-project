#ifndef INCLUDE_CNFG_PERIPHERALS_H
#define INCLUDE_CNFG_PERIPHERALS_H

#include "common.h"

// *******************pwm config******************* //
#define PWM_FREQUENCY 8000000
#define PWM_PERIOD    1000


// *******************BB driver******************* //

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

// *******************Encoders******************* //
#define MAX_TICK_ENCODER 360

// *******************Encoder 1******************//

#define ENCODER1_PHASE_A PAL_LINE(GPIOA, 4) //GREEN
#define ENCODER1_PHASE_B PAL_LINE(GPIOA, 3) // WHITE

// *******************Encoder 2******************//

#define ENCODER2_PHASE_A PAL_LINE(GPIOF, 3) //GREEN
#define ENCODER2_PHASE_B PAL_LINE(GPIOF, 5) // WHITE

// *******************Encoder 3******************//

#define ENCODER3_PHASE_A PAL_LINE(GPIOF, 1) //GREEN
#define ENCODER3_PHASE_B PAL_LINE(GPIOF, 2) // WHITE

// *******************Gyroscope******************//

#define SCL                     PAL_LINE(GPIOB, 8)
#define SDA                     PAL_LINE(GPIOB, 9)
#define AF_I2C                  4
#define ADDRESS_GYROSCOPE       0x6A
#define REGISTER_WHO_I_AM       0x0F
#define WHO_I_AM                0x6B
#define CTRL_REG2               0X11
#define VALUE_CTRL_REG2         0x7C
#define DATA_REGISTER           0x22
#define DELTA_TIME_GYRO         5

/**
 * @brief Init peripherals
 */
void cnfgInit(void);

#endif

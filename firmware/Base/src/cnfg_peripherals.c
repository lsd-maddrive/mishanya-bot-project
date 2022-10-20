#include "cnfg_peripherals.h"

/**
 * @brief Init pins and start PWM
 */
static void InitPwm(void);

static PWMConfig pwmcfg_m13 = {
  .frequency = PWM_FREQUENCY,
  .period = PWM_PERIOD,
  .callback = NULL,
  .channels = {
   {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_DISABLED, NULL}
  },
  .cr2 = 0,
  .bdtr = 0b11010110, //2 mcs
  .dier = 0
};

static PWMConfig pwmcfg_m23 = {
  .frequency = PWM_FREQUENCY,
  .period = PWM_PERIOD,
  .callback = NULL,
  .channels = {
   {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_DISABLED, NULL}
  },
  .cr2 = 0,
  .bdtr = 0b11010110, //2 mcs
  .dier = 0
};

void cnfgInit(void)
{
    InitPwm();
}

static void InitPwm(void)
{
    palSetLineMode(MOTOR1_PWM_HIN1, M1_AF_H1L1);
    palSetLineMode(MOTOR1_PWM_LIN1, M1_AF_H1L1);
    palSetLineMode(MOTOR1_PWM_HIN2, M1_AF_H2L2);
    palSetLineMode(MOTOR1_PWM_LIN2, M1_AF_H2L2);

    palSetLineMode(MOTOR2_PWM_HIN1, M2_AF_H1L1);
    palSetLineMode(MOTOR2_PWM_LIN1, M2_AF_H1L1);
    palSetLineMode(MOTOR2_PWM_HIN2, M2_AF_H2L2);
    palSetLineMode(MOTOR2_PWM_LIN2, M2_AF_H2L2);

    palSetLineMode(MOTOR3_PWM_HIN1, M3_AF_H1L1);
    palSetLineMode(MOTOR3_PWM_LIN1, M3_AF_H1L1);
    palSetLineMode(MOTOR3_PWM_HIN2, M3_AF_H2L2);
    palSetLineMode(MOTOR3_PWM_LIN2, M3_AF_H2L2);

    pwmStart(&PWMD1, &pwmcfg_m13);
    pwmStart(&PWMD8, &pwmcfg_m23);
}

#include <arm_driver.h>
#include <common.h>

#define UP_ARM 			PAL_LINE(GPIOB,4)
#define DOWN_ARM 		PAL_LINE(GPIOB,10)

#define LEFT_ARM_PWM 	PAL_LINE(GPIOA,8)
#define RIGHT_ARM_PWM 	PAL_LINE(GPIOA,9)

#define LEFT_ACTIVE		PWM_OUTPUT_ACTIVE_HIGH
#define RIGHT_ACTIVE	PWM_OUTPUT_ACTIVE_HIGH


static PWMDriver *ARM_DRIVER = &PWMD1;

/*** arm driver config ***/
PWMConfig ARM_CONF = {
    .frequency = PWM1_frequency,
    .period    = PWM1_period,
    .callback  = NULL,
    .channels  = {
                  {.mode = RIGHT_ACTIVE, .callback = NULL},
                  {.mode = LEFT_ACTIVE, .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

/**
 * @brief   Initialize arm driver
 */
void ARM_DRIVER_init(void)
{
    palSetLineMode(RIGHT_ARM_PWM, PAL_MODE_ALTERNATE(1));
    palSetLineMode(LEFT_ARM_PWM, PAL_MODE_ALTERNATE(1));
    palSetLineMode(DOWN_ARM, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(UP_ARM, PAL_MODE_OUTPUT_PUSHPULL);

    pwmStart(ARM_DRIVER, &ARM_CONF);
}

/**
 * @brief recieve the hand number and the filling period
 * the function controls the raising of the hand up
 */
void ARM_up(int ARM, uint16_t PWM_period)
{
    pwmEnableChannel(ARM_DRIVER, ARM, PWM_period);
    palWriteLine(UP_ARM, PAL_HIGH);
    palWriteLine(DOWN_ARM, PAL_LOW);
}

/**
 * @brief recieve the hand number and the filling period
 * the function controls the raising of the hand down
 */
void ARM_down(int ARM, uint16_t PWM_period)
{
    pwmEnableChannel(ARM_DRIVER, ARM, PWM_period);
    palWriteLine(DOWN_ARM, PAL_HIGH);
    palWriteLine(UP_ARM, PAL_LOW);
}

/**
 * @brief recieve the hand number
 * the function disables the selected hand
 */
void Off_ARM (int ARM)
{
    pwmDisableChannel(ARM_DRIVER, ARM);
}


////
//// Created by Anton on 09.09.2022.
////
#include "low_level.h"

#define PWM_frequency		500000
#define PWM_period			10000

static void init_gpio(void);
static void init_pwm(void);

// *******************arm spi config******************* //

// *******************arm spi config******************* //

// *******************arm pwm config******************* //

const PWMConfig pwm1config = {
        .frequency = PWM_frequency,
        .period    = PWM_period,
        .callback  = NULL,
        .channels  = {
                {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // E8  - LEFT_PWM_SHOULDER_IN
                {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // E11 - LEFT_PWM_SHOULDER_OUT
                {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // E13 - LEFT_PWM_ELBOW
                {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
        },
        .cr2        = 0,
        .dier       = 0
};

const PWMConfig pwm8config = {
        .frequency = PWM_frequency,
        .period    = PWM_period,
        .callback  = NULL,
        .channels  = {
                {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// C6 - RIGHT_PWM_SHOULDER_IN
                {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// C7 - RIGHT_PWM_SHOULDER_OUT
                {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
                {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}	// C9 - RIGHT_PWM_ELBOW
        },
        .cr2        = 0,
        .dier       = 0
};
// *******************arm pwm config******************* //

void init_low_level(void)
{
	init_gpio();
  init_pwm();
}

static void init_gpio(void)
{
	palSetLineMode(LEFT_UP_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LEFT_DOWN_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LEFT_PWM_ELBOW, PAL_MODE_ALTERNATE(LEFT_ELBOW_ALT_FUNC_NUM));
  pwmStart(&PWMD1, &pwm1config);


  palSetLineMode(RIGHT_UP_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(RIGHT_DOWN_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(RIGHT_PWM_ELBOW, PAL_MODE_ALTERNATE(RIGHT_ELBOW_ALT_FUNC_NUM));
  pwmStart(&PWMD8, &pwm8config);

}

static void init_pwm(void)
{

}
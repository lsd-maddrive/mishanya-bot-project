#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#define UP_ARM 			PAL_LINE(GPIOB,10)
#define DOWN_ARM 		PAL_LINE(GPIOB,4)
#define RIGHT_ARM_PWM 	PAL_LINE(GPIOA,8)
#define LEFT_ARM_PWM 	PAL_LINE(GPIOA,9)

#define LEFT_ACTIVE		PWM_OUTPUT_ACTIVE_HIGH
#define RIGHT_ACTIVE	PWM_OUTPUT_ACTIVE_HIGH

#define PWM1_frequency	500000
#define PWM1_period		10000

#define up_period   	8000
#define down_period 	2000

enum {LEFT_ARM, RIGHT_ARM};

static PWMDriver *pwm1Driver = &PWMD1;


PWMConfig pwm1conf = {
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

void PWM_ARM_init(void)
{
    palSetLineMode(RIGHT_ARM_PWM, PAL_MODE_ALTERNATE(1));
    palSetLineMode(LEFT_ARM_PWM, PAL_MODE_ALTERNATE(1));
    palSetLineMode(DOWN_ARM, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(UP_ARM, PAL_MODE_OUTPUT_PUSHPULL);

    pwmStart(pwm1Driver, &pwm1conf );
}

void ARM_up(int ARM)
{
	pwmEnableChannel(pwm1Driver, ARM, up_period);
	palWriteLine(UP_ARM, PAL_HIGH);
	palWriteLine(DOWN_ARM, PAL_LOW);
}

void ARM_down(int ARM)
{
	pwmEnableChannel(pwm1Driver, ARM, down_period);
	palWriteLine(DOWN_ARM, PAL_HIGH);
	palWriteLine(UP_ARM, PAL_LOW);
}

//
//void ARM_blocking()
//{
//	palWriteLine(UP_ARM, PAL_HIGH);
//	palWriteLine(DOWN_ARM, PAL_HIGH);
//	palWriteLine(PWM_PIN, PAL_HIGH);
//}

void Off_ARM (int ARM)
{
	pwmDisableChannel(pwm1Driver, ARM);
}



int main(void) {

    chSysInit();
    halInit();

    PWM_ARM_init();

    ARM_up(RIGHT_ARM);
    chThdSleepSeconds(5);
    Off_ARM(RIGHT_ARM);
    ARM_down(LEFT_ARM);
    chThdSleepSeconds(5);
    Off_ARM(LEFT_ARM);
    while (1)
    {

    }

}

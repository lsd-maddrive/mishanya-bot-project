#include <arm_driver.h>

//#define UP_ARM_LEFT 		PAL_LINE(GPIOB,4)
//#define DOWN_ARM_LEFT 		PAL_LINE(GPIOB,10)
//
//#define UP_ARM_RIGHT 		PAL_LINE(GPIOB,5)
//#define DOWN_ARM_RIGHT 		PAL_LINE(GPIOB,3)
//
//#define LEFT_ARM_PWM_1 	PAL_LINE(GPIOA,8)
//#define RIGHT_ARM_PWM_1 PAL_LINE(GPIOA,9)
//
//#define LEFT_ARM_PWM_2 	PAL_LINE(GPIOA,10)
//#define RIGHT_ARM_PWM_2 PAL_LINE(GPIOA,11)

#define LEFT_ACTIVE_1	PWM_OUTPUT_ACTIVE_HIGH
#define RIGHT_ACTIVE_1	PWM_OUTPUT_ACTIVE_HIGH

#define LEFT_ACTIVE_2	PWM_OUTPUT_ACTIVE_HIGH
#define RIGHT_ACTIVE_2	PWM_OUTPUT_ACTIVE_HIGH


static PWMDriver *ARM_DRIVER = &PWMD1;



pwm_ctx_t pwm1_ctx = {
	.is_started = false,
	.driver_ptr = &PWMD1,
	.pwm_conf = {
		.frequency = PWM1_frequency,
		.period    = PWM1_period,
		.callback  = NULL,
		.channels  = {
					// A8
					{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
					// A9
					{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
					// A10
					{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
					// A11
					{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}
					},
		.cr2        = 0,
		.dier       = 0
	}
}

/**
 * Settings - context space
 */ 

driver_ctx_t left_arm = {
	.type = BB,
	.pwm_ctx = &pwm1_ctx,
	.pins = {
		.up = PAL_LINE(GPIOB,4),
		.down = PAL_LINE(GPIOB,10),
		.PWM_1 = PAL_LINE(GPIOA,8),
		.PWM_2 = PAL_LINE(GPIOA,10),
	},
	.upper_limit = 10000;
	.lower_limit = 10;

	.k_rate = ...,
	.b_rate = ...
};

void init_ctx_limits(driver_ctx_t *ctx) {

}

int remap_percentage_2_raw(driver_ctx_t *ctx, int perc) {

}

driver_ctx_t right_arm = {
	.type = BB,
	.ch_side = &pwm1_ctx,
	.pins = {
		// TODO - refactoring
		.up = PAL_LINE(GPIOB,4),
		.down = PAL_LINE(GPIOB,10),
		.PWM_1 = PAL_LINE(GPIOA,8),
		.PWM_2 = PAL_LINE(GPIOA,10),
	},
};

driver_ctx_t *arms_ctxs[2] = {
	&left_arm, &right_arm
}


// TODO - refactoring

/*** arm driver config ***/
const PWMConfig ARM_CONF_RED = {
   .frequency = PWM1_frequency,
   .period    = PWM1_period,
   .callback  = NULL,
   .channels  = {
                 {.mode = RIGHT_ACTIVE_1, .callback = NULL},
                 {.mode = LEFT_ACTIVE_1, .callback = NULL},
                 {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL},
                 {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL}
                 },
   .cr2        = 0,
   .dier       = 0
};

const PWMConfig ARM_CONF_SELF_MADE = {
    .frequency = PWM1_frequency,
    .period    = PWM1_period,
    .callback  = NULL,
    .channels  = {
                  {.mode = RIGHT_ACTIVE_1	, .callback = NULL},
                  {.mode = LEFT_ACTIVE_1, .callback = NULL},
                  {.mode = RIGHT_ACTIVE_2,    .callback = NULL},
                  {.mode = LEFT_ACTIVE_2,    .callback = NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

const arm_t RIGHT_ARM = {
    .up = PAL_LINE(GPIOB,5),
    .down = PAL_LINE(GPIOB,3),
    .PWM_1 = PAL_LINE(GPIOA,9),
    .PWM_2 = PAL_LINE(GPIOA,11),
};

const arm_t LEFT_ARM = {
    .up = PAL_LINE(GPIOB,4),
    .down = PAL_LINE(GPIOB,10),
    .PWM_1 = PAL_LINE(GPIOA,8),
    .PWM_2 = PAL_LINE(GPIOA,10),
};

const PAL_STM32_bits down_left = {
		.bit_OUTPUT = 1,
		.bit_PUSHPULL = 0,
		.bit_ALTERNATE = 0,
		.bit_ALTERNATE_N = 0
};

const PAL_STM32_bits up_left = {
		.bit_OUTPUT = 1,
		.bit_PUSHPULL = 0,
		.bit_ALTERNATE = 0,
		.bit_ALTERNATE_N = 0
};

const PAL_STM32_bits down_right = {
		.bit_OUTPUT = 1,
		.bit_PUSHPULL = 0,
		.bit_ALTERNATE = 0,
		.bit_ALTERNATE_N = 0
};

const PAL_STM32_bits up_right = {
		.bit_OUTPUT = 1,
		.bit_PUSHPULL = 0,
		.bit_ALTERNATE = 0,
		.bit_ALTERNATE_N = 0
};


const init_digital_t DIGITAL_PIN = {down_left, up_left, down_right, up_right};


const PAL_STM32_bits pwm_right_1_self = {
		.bit_OUTPUT = 0,
		.bit_PUSHPULL = 0,
		.bit_ALTERNATE = 2,
		.bit_ALTERNATE_N = 1
};

const PAL_STM32_bits pwm_right_2_self = {
		.bit_OUTPUT = 0,
		.bit_PUSHPULL = 0,
		.bit_ALTERNATE = 2,
		.bit_ALTERNATE_N = 1
};

const PAL_STM32_bits pwm_left_1_self = {
		.bit_OUTPUT = 0,
		.bit_PUSHPULL = 0,
		.bit_ALTERNATE = 2,
		.bit_ALTERNATE_N = 1
};

const PAL_STM32_bits pwm_left_2_self = {
		.bit_OUTPUT = 0,
		.bit_PUSHPULL = 0,
		.bit_ALTERNATE = 2,
		.bit_ALTERNATE_N = 1
};

const init_pwm_t PWM_PIN_SELF = {pwm_right_1_self, pwm_right_2_self, pwm_left_1_self, pwm_left_2_self};

const PAL_STM32_bits pwm_right_1_red = {
		.bit_OUTPUT = 0,
		.bit_PUSHPULL = 0,
		.bit_ALTERNATE = 2,
		.bit_ALTERNATE_N = 1
};

const PAL_STM32_bits pwm_right_2_red = {
		.bit_OUTPUT = 0,
		.bit_PUSHPULL = 0,
		.bit_ALTERNATE = 0,
		.bit_ALTERNATE_N = 0
};

const PAL_STM32_bits pwm_left_1_red = {
		.bit_OUTPUT = 0,
		.bit_PUSHPULL = 0,
		.bit_ALTERNATE = 2,
		.bit_ALTERNATE_N = 1
};

const PAL_STM32_bits pwm_left_2_red = {
		.bit_OUTPUT = 0,
		.bit_PUSHPULL = 0,
		.bit_ALTERNATE = 0,
		.bit_ALTERNATE_N = 0
};

const init_pwm_t PWM_PIN_RED = {pwm_right_1_red, pwm_right_2_red, pwm_left_1_red, pwm_left_2_red};


init_driver_t SELF_DRIVER = {
	.pwm_mode = PWM_PIN_SELF, 
	.digital_mode = DIGITAL_PIN, 
	.left_arm = LEFT_ARM, 
	.right_arm = RIGHT_ARM, 
	.pwm_conf = ARM_CONF_SELF_MADE};
init_driver_t RED_DRIVER = {PWM_PIN_RED, DIGITAL_PIN, LEFT_ARM, RIGHT_ARM, ARM_CONF_RED};

/**
 * @brief   Initialize arm driver
 */
void ARM_DRIVERS_init()
{
	if (left_arm.type == RED) {
		lld_red_init_driver(&left_arm);
	}

    // palSetLineMode(init.right_arm.PWM_1, (init.pwm_mode.right1_pwm.bit_ALTERNATE << 0) | (init.pwm_mode.right1_pwm.bit_ALTERNATE_N << 7));
    // palSetLineMode(init.left_arm.PWM_1, (init.pwm_mode.left1_pwm.bit_ALTERNATE << 0) | (init.pwm_mode.left1_pwm.bit_ALTERNATE_N << 7));
    // palSetLineMode(init.right_arm.PWM_2, (init.pwm_mode.right2_pwm.bit_ALTERNATE << 0) | (init.pwm_mode.right2_pwm.bit_ALTERNATE_N << 7));
    // palSetLineMode(init.left_arm.PWM_2,  (init.pwm_mode.left2_pwm.bit_ALTERNATE << 0) | (init.pwm_mode.left2_pwm.bit_ALTERNATE_N << 7));
    // palSetLineMode(init.left_arm.down, (init.digital_mode.left_down.bit_OUTPUT << 0) | (init.digital_mode.left_down.bit_PUSHPULL << 2));
    // palSetLineMode(init.left_arm.up, (init.digital_mode.left_up.bit_OUTPUT << 0) | (init.digital_mode.left_up.bit_PUSHPULL << 2));
    // palSetLineMode(init.right_arm.down, (init.digital_mode.right_down.bit_OUTPUT << 0) | (init.digital_mode.right_down.bit_PUSHPULL << 2));
    // palSetLineMode(init.right_arm.up, (init.digital_mode.right_up.bit_OUTPUT << 0) | (init.digital_mode.right_up.bit_PUSHPULL << 2));

    // pwmStart(ARM_DRIVER, &init.pwm_conf);
}


//void ARM_DRIVER_init(void)
//{
//    palSetLineMode(RIGHT_ARM_PWM_1, PAL_MODE_ALTERNATE(1));
//    palSetLineMode(LEFT_ARM_PWM_1, PAL_MODE_ALTERNATE(1));
//    palSetLineMode(RIGHT_ARM_PWM_2, PAL_MODE_ALTERNATE(1));
//    palSetLineMode(LEFT_ARM_PWM_2, PAL_MODE_ALTERNATE(1));
//    palSetLineMode(DOWN_ARM_LEFT, PAL_MODE_OUTPUT_PUSHPULL);
//    palSetLineMode(UP_ARM_LEFT, PAL_MODE_OUTPUT_PUSHPULL);
//    palSetLineMode(DOWN_ARM_RIGHT, PAL_MODE_OUTPUT_PUSHPULL);
//    palSetLineMode(UP_ARM_RIGHT, PAL_MODE_OUTPUT_PUSHPULL);
//
//    pwmStart(ARM_DRIVER, &ARM_CONF_SELF_MADE);
//}

/**
 * @brief recieve the hand number and the filling period
 * the function controls the raising of the hand up
 */
void ARM_up(ARM_SIDE_t side, uint16_t PWM_period)
{
	driver_ctx_t *ctx = arms_ctxs[side];

//   pwmEnableChannel(ARM_DRIVER, ARM.arm, PWM_period);
//   palWriteLine(ARM.up, PAL_HIGH);
//   palWriteLine(ARM.down, PAL_LOW);
}

//
// void test_new_driver(arm_t ARM, uint16_t PWM_period)
// {
//     pwmEnableChannel(ARM_DRIVER, ARM, PWM_period);
//    palWriteLine(UP_ARM_LEFT, PAL_HIGH);
//    palWriteLine(DOWN_ARM_LEFT, PAL_LOW);
// }
//
///**
// * @brief recieve the hand number and the filling period
// * the function controls the raising of the hand down
// */
//void ARM_down(arm_t ARM, uint16_t PWM_period)
//{
//    pwmEnableChannel(ARM_DRIVER, ARM, PWM_period);
//    palWriteLine(DOWN_ARM_1, PAL_HIGH);
//    palWriteLine(UP_ARM_1, PAL_LOW);
//}
//
///**
// * @brief recieve the hand number
// * the function disables the selected hand
// */
//void Off_ARM (arm_t ARM, ioline_t)
//{
//   pwmDisableChannel(ARM_DRIVER, ARM);
//   palWriteLine(DOWN_ARM_LEFT, PAL_LOW);
//   palWriteLine(UP_ARM_LEFT, PAL_LOW);
//}


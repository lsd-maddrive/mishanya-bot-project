#include <elbow_driver.h>

#define PWM_frequency	500000
#define PWM_period		10000

#define BB_DRIVER 			1
#define RED_DRIVER 			2
#define DRIVER 				RED_DRIVER

const PWMDriver *ELBOW_DRIVER_PTR_3_TIM = &PWMD3;

const PWMDriver *ELBOW_DRIVER_PTR_4_TIM = &PWMD4;

#if(DRIVER == RED_DRIVER)

	#define LEFT_UP 		PAL_LINE(GPIOB,4)
	#define LEFT_DOWN 		PAL_LINE(GPIOB,10)
	#define LEFT_PWM 		PAL_LINE(GPIOA,6) // TIM3 CH1

	#define RIGHT_UP 		PAL_LINE(GPIOB,5)
	#define RIGHT_DOWN 		PAL_LINE(GPIOB,3)
	#define RIGHT_PWM 		PAL_LINE(GPIOB,6) // TIM4 CH1

#endif

#if(DRIVER == BB_DRIVER)

	#define LEFT_UP 		PAL_LINE(GPIOB,4)
	#define LEFT_DOWN 		PAL_LINE(GPIOB,10)
	#define LEFT_PWM_1 		PAL_LINE(GPIOA,6) // TIM3 CH1
	#define LEFT_PWM_2 		PAL_LINE(GPIOA,7) // TIM3 CH2

	#define RIGHT_UP 		PAL_LINE(GPIOB,5)
	#define RIGHT_DOWN 		PAL_LINE(GPIOB,3)
	#define RIGHT_PWM_1 	PAL_LINE(GPIOB,6) // TIM4 CH1
	#define RIGHT_PWM_2 	PAL_LINE(GPIOB,7) // TIM3 CH2

#endif



#if(DRIVER == RED_DRIVER)

	const pwm_channel_t ch_left_pwm = {
		.alt_func_1 = 2,
		.ch_pwm_1 = 0
	};

	const pwm_channel_t ch_right_pwm = {
		.alt_func_1 = 2,
		.ch_pwm_1 = 1
	};

	const pwm_ctx_t left_pwm_ctx = {
		.pwm_ch = ch_left_pwm,
		.driver_ptr = &PWMD3,
		.pwm_conf = {
			.frequency = PWM_frequency,
			.period    = PWM_period,
			.callback  = NULL,
			.channels  = {
						 
						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}, // LEFT_PWM
						
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
						
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
						
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
						},
			.cr2        = 0,
			.dier       = 0
		}
	};

	const pwm_ctx_t right_pwm_ctx = {
		.pwm_ch = ch_right_pwm,
		.driver_ptr = &PWMD4,
		.pwm_conf = {
			.frequency = PWM_frequency,
			.period    = PWM_period,
			.callback  = NULL,
			.channels  = {
						
						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}, // RIGHT_PWM
						
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},

						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
						
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
						},
			.cr2        = 0,
			.dier       = 0
		}
	};

	const line_driver_t left_control = {
			.PWM_1 = LEFT_PWM,
			.digit_2 = LEFT_DOWN,
			.digit_1 = LEFT_UP
	};

	const line_driver_t right_control = {
			.PWM_1 = RIGHT_PWM,
			.digit_2 = RIGHT_DOWN,
			.digit_1 = RIGHT_UP
	};

	const control_driver_t left_arm = {
		.line_control = left_control,
		.arm_ctx = left_pwm_ctx,
	};

	const control_driver_t right_arm = {
		.line_control = right_control,
		.arm_ctx = right_pwm_ctx,
	};

	const arm_driver_ctx_t elbow_driver = {
		.type = RED,
		.arm[0] = left_arm,
		.arm[1] = right_arm
	};

#endif

#if(DRIVER == BB_DRIVER)

	const pwm_channel_t ch_left_pwm = {
		.alt_func_1 = 2,
		.ch_pwm_1 = 0
	};

	const pwm_channel_t ch_right_pwm = {
		.alt_func_1 = 2,
		.ch_pwm_1 = 1
	};

	const pwm_ctx_t left_pwm_ctx = {
		.driver_ptr = &PWMD3,
		.pwm_conf = {
			.frequency = PWM_frequency,
			.period    = PWM_period,
			.callback  = NULL,
			.channels  = {
						// LEFT_PWM_1
						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
						// LEFT_PWM_2
						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
						
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
						
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
						},
			.cr2        = 0,
			.dier       = 0
		}
	};

	const pwm_ctx_t right_pwm_ctx = {
		.driver_ptr = &PWMD4,
		.pwm_conf = {
			.frequency = PWM_frequency,
			.period    = PWM_period,
			.callback  = NULL,
			.channels  = {
						
						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
						
						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
						// RIGHT_PWM_1
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
						// RIGHT_PWM_2
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
						},
			.cr2        = 0,
			.dier       = 0
		}
	};

	const line_driver_t left_control = {
			.PWM_1 = LEFT_PWM_1,
			.PWM_2 = LEFT_PWM_2,
			.digit_2 = LEFT_DOWN,
			.digit_1 = LEFT_UP
	};

	const line_driver_t right_control = {
			.PWM_1 = RIGHT_PWM_1,
			.PWM_2 = RIGHT_PWM_2,
			.digit_2 = RIGHT_DOWN,
			.digit_1 = RIGHT_UP
	};

	const control_driver_t left_arm = {
		.line_control = left_control,
		.arm_ctx = left_pwm_ctx
	};

	const control_driver_t right_arm = {
		.line_control = right_control,
		.arm_ctx = right_pwm_ctx
	};

	const arm_driver_ctx_t elbow_driver = {
		.type = BB,
		.arm[0] = left_arm,
		.arm[1] = right_arm
	};

#endif


/**
 * @brief   Initialize arm driver
 */
void elbow_init(void)
{
	driver_init(&elbow_driver);
}

void elbow_up(arm_side_t side, uint16_t period)
{
	arm_up(side, &elbow_driver, period);
}

void elbow_down(arm_side_t side, uint16_t period)
{
	arm_down(side, &elbow_driver, period);
}

void elbow_off(arm_side_t side)
{
	arm_off(side, &elbow_driver);
}


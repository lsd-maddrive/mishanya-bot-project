#include <elbow_driver.h>

#define PWM_frequency	500000
#define PWM_period		10000

#define BB_DRIVER 			1
#define RED_DRIVER 			2
#define DRIVER 				BB_DRIVER

const PWMDriver *ELBOW_DRIVER = &PWMD3;

#if(DRIVER == RED_DRIVER)

	#define LEFT_UP 		PAL_LINE(GPIOB,4)
	#define LEFT_DOWN 		PAL_LINE(GPIOB,10)
	#define LEFT_PWM 		PAL_LINE(GPIOA,6) // TIM3 CH1

	#define RIGHT_UP 		PAL_LINE(GPIOB,5)
	#define RIGHT_DOWN 		PAL_LINE(GPIOB,3)
	#define RIGHT_PWM 		PAL_LINE(GPIOB,0) // TIM3 CH3

#endif

#if(DRIVER == BB_DRIVER)

	#define LEFT_UP 		PAL_LINE(GPIOB,4)
	#define LEFT_DOWN 		PAL_LINE(GPIOB,10)
	#define LEFT_PWM_1 		PAL_LINE(GPIOA,6) // TIM3 CH1
	#define LEFT_PWM_2 		PAL_LINE(GPIOB,7) // TIM3 CH2

	#define RIGHT_UP 		PAL_LINE(GPIOB,7)
	#define RIGHT_DOWN 		PAL_LINE(GPIOB,3)
	#define RIGHT_PWM_1 	PAL_LINE(GPIOB,0) // TIM3 CH3
	#define RIGHT_PWM_2 	PAL_LINE(GPIOB,1) // TIM3 CH4

#endif



#if(DRIVER == RED_DRIVER)

	const pwm_ctx_t left_pwm_ctx = {
		.is_started = false,
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
		.is_started = false,
		.driver_ptr = &PWMD3,
		.pwm_conf = {
			.frequency = PWM_frequency,
			.period    = PWM_period,
			.callback  = NULL,
			.channels  = {
						
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL}, // RIGHT_PWM
						
						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
						
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
						
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
						},
			.cr2        = 0,
			.dier       = 0
		}
	};

	const control_driver_t left_control = {
			.PWM_1 = LEFT_PWM,
			.down = LEFT_DOWN,
			.up = LEFT_UP
	};

	const control_driver_t right_control = {
			.PWM_1 = RIGHT_PWM,
			.down = RIGHT_DOWN,
			.up = RIGHT_UP
	};

	const arm_t left_arm = {
		.arm_control = left_control,
		.arm_ctx = left_pwm_ctx
	};

	const arm_t right_arm = {
		.arm_control = right_control,
		.arm_ctx = right_pwm_ctx
	};

	const driver_ctx_t elbow_driver = {
		.type = RED,
		.left = left_arm,
		.right = right_arm
	};

#endif

#if(DRIVER == BB_DRIVER)

	const pwm_ctx_t left_pwm_ctx = {
		.is_started = false,
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
		.is_started = false,
		.driver_ptr = &PWMD3,
		.pwm_conf = {
			.frequency = PWM_frequency,
			.period    = PWM_period,
			.callback  = NULL,
			.channels  = {
						
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
						
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
						// RIGHT_PWM_1
						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
						// RIGHT_PWM_2
						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}
						},
			.cr2        = 0,
			.dier       = 0
		}
	};

	const control_driver_t left_control = {
			.PWM_1 = LEFT_PWM_1,
			.PWM_2 = LEFT_PWM_2,
			.down = LEFT_DOWN,
			.up = LEFT_UP
	};

	const control_driver_t right_control = {
			.PWM_1 = RIGHT_PWM_1,
			.PWM_2 = RIGHT_PWM_2,
			.down = RIGHT_DOWN,
			.up = RIGHT_UP
	};

	const arm_t left_arm = {
		.arm_control = left_control,
		.arm_ctx = left_pwm_ctx
	};

	const arm_t right_arm = {
		.arm_control = right_control,
		.arm_ctx = right_pwm_ctx
	};

	const driver_ctx_t elbow_driver = {
		.type = BB,
		.left = left_arm,
		.right = right_arm
	};

#endif





#include <elbow_driver.h>



#define BB_DRIVER 			1
#define RED_DRIVER 			2
#define DRIVER 				RED_DRIVER

static PWMDriver *ARM_DRIVER_LEFT = &PWMD1;
static PWMDriver *ARM_DRIVER_RIGHT = &PWMD2;

//#if(DRIVER == RED_DRIVER)

	#define LEFT_UP 		PAL_LINE(GPIOB,4)
	#define LEFT_DOWN 		PAL_LINE(GPIOB,10)
	#define LEFT_PWM 		PAL_LINE(GPIOA,8)

	#define RIGHT_UP 		PAL_LINE(GPIOB,5)
	#define RIGHT_DOWN 		PAL_LINE(GPIOB,3)
	#define RIGHT_PWM 		PAL_LINE(GPIOA,9)

//#elif
//
//	#define LEFT_UP 		PAL_LINE(GPIOB,4)
//	#define LEFT_DOWN 		PAL_LINE(GPIOB,10)
//	#define LEFT_PWM_1 		PAL_LINE(GPIOA,8)
//	#define LEFT_PWM_2 		PAL_LINE(GPIOA,10)
//
//	#define RIGHT_UP 		PAL_LINE(GPIOB,5)
//	#define RIGHT_DOWN 		PAL_LINE(GPIOB,3)
//	#define RIGHT_PWM_1 	PAL_LINE(GPIOA,9)
//	#define RIGHT_PWM_2 	PAL_LINE(GPIOA,11)
//
//#endif



//#if(DRIVER == RED_DRIVER)

	pwm_ctx_t left_pwm_ctx = {
		.is_started = false,
		.driver_ptr = &PWMD1,
		.pwm_conf = {
			.frequency = PWM_frequency,
			.period    = PWM_period,
			.callback  = NULL,
			.channels  = {
						// A8
						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
						// A9
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
						// A10
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
						// A11
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
						},
			.cr2        = 0,
			.dier       = 0
		}
	};

	pwm_ctx_t right_pwm_ctx = {
		.is_started = false,
		.driver_ptr = &PWMD2,
		.pwm_conf = {
			.frequency = PWM_frequency,
			.period    = PWM_period,
			.callback  = NULL,
			.channels  = {
						// A8
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
						// A9
						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
						// A10
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
						// A11
						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
						},
			.cr2        = 0,
			.dier       = 0
		}
	};

	control_driver_t left_control = {
			.PWM_1 = LEFT_PWM,
			.down = LEFT_DOWN,
			.up = LEFT_UP
	};

	control_driver_t right_control = {
			.PWM_1 = RIGHT_PWM,
			.down = RIGHT_DOWN,
			.up = RIGHT_UP
	};

	arm_t left_arm = {
		.arm_control = left_control,
		.arm_ctx = left_pwm_ctx
	};

	arm_t right_arm = {
		.arm_control = right_control,
		.arm_ctx = right_pwm_ctx
	};

	driver_ctx_t elbow_driver = {
		.type = RED,
		.left = left_arm,
		.right = right_arm
	};

//#elif
//
//	pwm_ctx_t left_pwm_ctx = {
//		.is_started = false,
//		.driver_ptr = &PWMD1,
//		.pwm_conf = {
//			.frequency = PWM_frequency,
//			.period    = PWM_period,
//			.callback  = NULL,
//			.channels  = {
//						// A8
//						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
//						// A9
//						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
//						// A10
//						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
//						// A11
//						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
//						},
//			.cr2        = 0,
//			.dier       = 0
//		}
//	}
//
//	pwm_ctx_t right_pwm_ctx = {
//		.is_started = false,
//		.driver_ptr = &PWMD2,
//		.pwm_conf = {
//			.frequency = PWM_frequency,
//			.period    = PWM_period,
//			.callback  = NULL,
//			.channels  = {
//						// A8
//						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
//						// A9
//						{.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
//						// A10
//						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
//						// A11
//						{.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}
//						},
//			.cr2        = 0,
//			.dier       = 0
//		}
//	}
//
//	control_driver_t left_control = {
//			.PWM_1 = LEFT_PWM_1,
//			.PWM_2 = LEFT_PWM_2,
//			.down = LEFT_DOWN,
//			.up = LEFT_UP
//	};
//
//	control_driver_t right_control = {
//			.PWM_1 = RIGHT_PWM_1,
//			.PWM_2 = RIGHT_PWM_2,
//			.down = RIGHT_DOWN,
//			.up = RIGHT_UP
//	};
//
//	arm_t left_arm = {
//		.arm_control = left_control,
//		.arm_ctx = left_pwm_ctx
//	};
//
//	arm_t right_arm = {
//		.arm_control = right_control,
//		.arm_ctx = right_pwm_ctx
//	};
//
//	driver_ctx_t elbow_driver = {
//		.type = BB,
//		.left = left_arm,
//		.right = right_arm
//	};
//
//#endif





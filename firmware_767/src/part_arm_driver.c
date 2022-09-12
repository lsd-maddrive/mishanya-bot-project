#include <part_arm_driver.h>
#include "robo_lib/lld_bb_driver.h"
#include "robo_lib/lld_red_driver.h"

// copy from elbow_driver
// TODO: need to fix -> look into drive_init
#define PWM_frequency		500000
#define PWM_period			10000

PWMDriver * const pwm1Driver_copy = &PWMD1;

const PWMConfig pwm1config_copy = {
  .frequency = PWM_frequency,
  .period    = PWM_period,
  .callback  = NULL,
  .channels  = {
		  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
		  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
		  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // E13 - LEFT_PWM_ELBOW
		  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
  },
  .cr2        = 0,
  .dier       = 0
};

PWMDriver * const pwm8Driver_copy = &PWMD8;

const PWMConfig pwm8config_copy = {
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

/**
 * @brief   initialize arm driver
 * @brief   receive arm struct
 */
void driver_init(arm_ctx_t *arm_driver)
{
//	// left arm part
//	line_driver_t pins_left_elbow = arm_driver->arm[LEFT].control.line_control;
//	pwm_ctx_t pwm_ctx_left_elbow = arm_driver->arm[LEFT].control.pwm_setting_ctx;
//
//	// right arm part
//	line_driver_t pins_left_shoulder_in = arm_driver->arm[RIGHT].control.line_control;
//	pwm_ctx_t pwm_ctx_left_shoulder_in = arm_driver->arm[RIGHT].control.pwm_setting_ctx;
//
//	if (arm_driver->type == RED)
//	{
//		// left arm
//		lld_red_init_driver(&pins_left_elbow, &pwm_ctx_left_elbow);
//
//		// right arm
//        lld_red_init_driver(&pins_right_elbow, &pwm_ctx_right_elbow);
//	}
//	else
//	{
//		// TODO: need to check and debug
//		lld_bb_init_driver(&pins_right_elbow, &pwm_ctx_right_elbow);
//		lld_bb_init_driver(&pins_left_elbow, &pwm_ctx_left_elbow);
//
//		lld_bb_init_driver(&pins_right_shoulder_in, &pwm_ctx_right_shoulder_in);
//		lld_bb_init_driver(&pins_left_shoulder_in, &pwm_ctx_left_shoulder_in);
//
//		lld_bb_init_driver(&pins_right_shoulder_out, &pwm_ctx_right_shoulder_out);
//		lld_bb_init_driver(&pins_left_shoulder_out, &pwm_ctx_left_shoulder_out);
//	}
//
//	pwmStart(pwm1Driver_copy, &pwm1config_copy);
//	pwmStart(pwm8Driver_copy, &pwm8config_copy);

}

/**
 * @brief the function controls the raising of the hand up
 * @brief recieve the hand side, arm struct and the filling period
 */
void arm_up(arm_side_t side, arm_ctx_t *arm_driver, uint16_t period)
{

	control_driver_t control = arm_driver->arm[side].traking_cs.control;

	if (arm_driver->type == RED)
    {
        lld_red_driver_direct(&control, period);
    }
	else
    {
        lld_bb_driver_direct(&control, period);
    }
}

/**
 * @brief the function controls the raising of the hand down
 * @brief recieve the hand side, arm struct and the filling period
 */
void arm_down(arm_side_t side, arm_ctx_t *arm_driver, uint16_t period)
{

	control_driver_t control = arm_driver->arm[side].traking_cs.control;

	if (arm_driver->type == RED)
    lld_red_driver_reverse(&control, period);
	else
    lld_bb_driver_reverse(&control, period);

}


/**
 * @brief the function disables the selected hand
 * @brief recieve the hand side, arm struct
 */
void arm_off (arm_side_t side, arm_ctx_t *arm_driver)
{

	control_driver_t control = arm_driver->arm[side].traking_cs.control;
	if (arm_driver->type == RED)
	{
		lld_red_driver_off(&control);
	}
	else
		lld_bb_driver_off(&control);
}

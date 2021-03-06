#include <elbow_driver.h>


// *******************elbow driver type config******************* //

#define BB_DRIVER       1
#define RED_DRIVER      2
#define DRIVER          RED_DRIVER

// *******************elbow driver type config******************* //

// *******************elbow driver PWM config******************* //

#define PWM_frequency		500000
#define PWM_period			10000

// *******************elbow driver PWM config******************* //


// **********************close sys config********************** //

#define ENCODER_DEADZONE 1
#define INTEGRAL_PERIOD 100

// **********************close sys config********************** //

// *******************elbow driver pin config******************* //

#if(DRIVER == RED_DRIVER)

	#define LEFT_UP			PAL_LINE(GPIOB,4)
	#define LEFT_DOWN		PAL_LINE(GPIOB,10)
	#define LEFT_PWM		PAL_LINE(GPIOA,6) // TIM3 CH1

	#define RIGHT_UP		PAL_LINE(GPIOB,5)
	#define RIGHT_DOWN	PAL_LINE(GPIOB,3)

	#define RIGHT_PWM		PAL_LINE(GPIOC,7) // TIM3 CH2

#endif

#if(DRIVER == BB_DRIVER)

	#define LEFT_UP			PAL_LINE(GPIOB,4)
	#define LEFT_DOWN		PAL_LINE(GPIOB,10)
	#define LEFT_PWM_1	PAL_LINE(GPIOA,8) // TIM1 CH1
	#define LEFT_PWM_2	PAL_LINE(GPIOA,7) // TIM1 CH1N

	#define RIGHT_UP		PAL_LINE(GPIOB,5)
	#define RIGHT_DOWN	PAL_LINE(GPIOB,3)
	#define RIGHT_PWM_1	PAL_LINE(GPIOA,9) // TIM1 CH2
	#define RIGHT_PWM_2	PAL_LINE(GPIOB,0) // TIM1 CH2N

#endif

// *******************elbow driver pin config******************* //


// ***************************PID coef************************** //

PID_t elbow_PID = {
  .coef = {.kp = 3000, .ki = 500, .kd = 0},
  .error = {.P = 0, .prev_P = 0, .I = 0, .D = 0}
};

// ***************************PID coef************************** //

// ***************************angle lim************************* //

const angle_lim_t right_angle_lim = {
  .max_angle = 62.6660,
  .min_angle = 22.9394
};

const angle_lim_t left_angle_lim = {
  .max_angle = 18.2812,
  .min_angle = 334.9511
};

// ***************************angle lim************************** //



#if(DRIVER == RED_DRIVER)

// ***********************left arm config*********************** //

	const pwm_channel_t ch_left_pwm = {
    .alt_func_1 = 2,
    .ch_pwm_1 = 0
	};

	const pwm_ctx_t left_pwm_ctx = {
    .pwm_ch = ch_left_pwm,
    .driver_ptr = &PWMD3,
    .pwm_conf = {
      .frequency = PWM_frequency,
      .period    = PWM_period,
      .callback  = NULL,
      .channels  = {

    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// LEFT_PWM

    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// RIGHT_PWM

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

  const control_driver_t left_arm = {
    .line_control = left_control,
    .arm_ctx = left_pwm_ctx
  };

  const close_conf_t left_close_conf = {
    .angle_lim = left_angle_lim,
    .angle_dead_zone = ENCODER_DEADZONE,
    .dt = INTEGRAL_PERIOD
  };

  const arm_system_t left_system = {
    .close_conf = left_close_conf,
    .control = left_arm
  };

// ***********************left arm config*********************** //


// ***********************right arm config*********************** //

	const pwm_channel_t ch_right_pwm = {
    .alt_func_1 = 2,
    .ch_pwm_1 = 1
	};

	const pwm_ctx_t right_pwm_ctx = {
    .pwm_ch = ch_right_pwm,
    .driver_ptr = &PWMD3,
    .pwm_conf = {
      .frequency = PWM_frequency,
      .period    = PWM_period,
      .callback  = NULL,
      .channels  = {

    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// LEFT_PWM

    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// RIGHT_PWM

    {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},

    {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}

      },
      .cr2        = 0,
      .dier       = 0
    }
	};

	const line_driver_t right_control = {
    .PWM_1 = RIGHT_PWM,
    .digit_2 = RIGHT_DOWN,
    .digit_1 = RIGHT_UP
	};

	const control_driver_t right_arm = {
    .line_control = right_control,
    .arm_ctx = right_pwm_ctx
	};

  const close_conf_t right_close_conf = {
    .angle_lim = right_angle_lim,
    .angle_dead_zone = ENCODER_DEADZONE,
    .dt = INTEGRAL_PERIOD
  };

  const arm_system_t right_system = {
    .close_conf = right_close_conf,
    .control = right_arm
  };

// ***********************right arm config*********************** //



// ***********************final config struct*********************** //

  const arm_driver_ctx_t elbow_driver = {
    .type = BB,
    .down = &elbow_down,
    .up = &elbow_up,
    .off = &elbow_off,
    .arm[0] = left_system,
    .arm[1] = right_system
  };


// ***********************final config struct*********************** //

#endif

#if(DRIVER == BB_DRIVER)

// ***********************left arm config*********************** //

	const pwm_channel_t ch_left_pwm = {
    .ch_pwm_1 = 0,
    .ch_pwm_2 = 0,
    .alt_func_1 = 1,
    .alt_func_2 = 1
	};

	const pwm_ctx_t left_pwm_ctx = {
    .pwm_ch = ch_left_pwm,
    .driver_ptr = &PWMD1,
    .pwm_conf = {
      .frequency = PWM_frequency,
      .period    = PWM_period,
      .callback  = NULL,
      .channels  = {

        {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// LEFT_PWM

        {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // RIGHT_PWM

        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},

        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}

      },
      .cr2        = 0,
    // !!!!!!!! THE CALCULATION WAS MADE FOR A CLOCK FREQUENCY OF 8 MHz AND THE APB1 BUS !!!!!!!! //
      .bdtr 		= 0b10011100,
    // !!!!!!!! THE CALCULATION WAS MADE FOR A CLOCK FREQUENCY OF 8 MHz AND THE APB1 BUS !!!!!!!! //
      .dier       = 0
    }
	};

	const line_driver_t left_control = {
    .PWM_1 = LEFT_PWM_1,
    .PWM_2 = LEFT_PWM_2,
    .digit_1 = LEFT_UP,
    .digit_2 = LEFT_DOWN
	};

  const control_driver_t left_arm = {
    .line_control = left_control,
    .arm_ctx = left_pwm_ctx
  };

  const close_conf_t left_close_conf = {
    .angle_lim = left_angle_lim,
    .angle_dead_zone = ENCODER_DEADZONE,
    .dt = INTEGRAL_PERIOD
  };

  const arm_system_t left_system = {
    .close_conf = left_close_conf,
    .control = left_arm
  };

// ***********************left arm config*********************** //

// ***********************right arm config*********************** //

	const pwm_channel_t ch_right_pwm = {
    .ch_pwm_1 = 1,
    .ch_pwm_2 = 1,
    .alt_func_1 = 1,
    .alt_func_2 = 1
	};

	const pwm_ctx_t right_pwm_ctx = {
    .pwm_ch = ch_right_pwm,
    .driver_ptr = &PWMD1,
    .pwm_conf = {
      .frequency = PWM_frequency,
      .period    = PWM_period,
      .callback  = NULL,
      .channels  = {

        {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// LEFT_PWM

        {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// RIGHT_PWM

        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},

        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}

      },
      .cr2        = 0,

    // !!!!!!!! THE CALCULATION WAS MADE FOR A CLOCK FREQUENCY OF 8 MHz AND THE APB1 BUS !!!!!!!! //
      .bdtr 		= 0b10011100,
    // !!!!!!!! THE CALCULATION WAS MADE FOR A CLOCK FREQUENCY OF 8 MHz AND THE APB1 BUS !!!!!!!! //

      .dier       = 0
    }
	};

	const line_driver_t right_control = {
    .PWM_1 = RIGHT_PWM_1,
    .PWM_2 = RIGHT_PWM_2,
    .digit_1 = RIGHT_UP,
    .digit_2 = RIGHT_DOWN
	};

	const control_driver_t right_arm = {
    .line_control = right_control,
    .arm_ctx = right_pwm_ctx
	};

  const close_conf_t right_close_conf = {
    .angle_lim = right_angle_lim,
    .angle_dead_zone = ENCODER_DEADZONE,
    .dt = INTEGRAL_PERIOD
  };

  const arm_system_t right_system = {
    .close_conf = right_close_conf,
    .control = right_arm
  };

// ***********************right arm config*********************** //

// ***********************final config struct*********************** //

	const arm_driver_ctx_t elbow_driver = {
    .type = BB,
    .down = &elbow_down,
    .up = &elbow_up,
    .off = &elbow_off,
    .arm[0] = left_system,
    .arm[1] = right_system
	};

// ***********************final config struct*********************** //

#endif


/**
 * @brief   initialize elbow driver
 */
void elbow_init(void)
{
  driver_init(&elbow_driver);
}

/**
 * @brief the function controls the raising of the elbow up
 * @brief recieve the hand side and the filling period
 */
void elbow_up(arm_side_t side, uint16_t period)
{
	arm_up(side, &elbow_driver, period);
}

/**
 * @brief the function controls the raising of the elbow down
 * @brief recieve the hand side and the filling period
 */
void elbow_down(arm_side_t side, uint16_t period)
{
	arm_down(side, &elbow_driver, period);
}

/**
 * @brief the function disables the selected elbow
 * @brief recieve the hand sides
 */
void elbow_off(arm_side_t side)
{
	arm_off(side, &elbow_driver);
}

/**
 * @brief the function set input angle (0-40)
 * @brief recieve the hand side and goal angle
 */
void elbow_set_angle(float goal_angle, arm_side_t side)
{
  close_sys_arm(goal_angle, side, &elbow_driver, &elbow_PID);
}


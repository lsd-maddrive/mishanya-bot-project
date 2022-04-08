#include "elbow_driver.h"



// *******************elbow driver type config******************* //

#define BB_DRIVER       0
#define RED_DRIVER      1
#define DRIVER          RED_DRIVER

// *******************elbow driver type config******************* //

// *******************elbow driver PWM config******************* //

#define PWM_frequency		500000
#define PWM_period			10000

// *******************elbow driver PWM config******************* //


// **********************close sys config********************** //

#define ENCODER_DEADZONE 1

// **********************close sys config********************** //

// *******************elbow driver pin config******************* //

#if(DRIVER == RED_DRIVER)

	#define LEFT_PWM		PAL_LINE(GPIOA,6) // TIM3 CH1
	#define RIGHT_PWM		PAL_LINE(GPIOC,7) // TIM3 CH2

  #define LEFT_UP			PAL_LINE(GPIOB,4)
  #define LEFT_DOWN		PAL_LINE(GPIOB,10)
  #define RIGHT_UP		PAL_LINE(GPIOB,5)
  #define RIGHT_DOWN	PAL_LINE(GPIOB,3)

#endif

#if(DRIVER == BB_DRIVER)


	#define LEFT_HIN_1 PAL_LINE(GPIOA,8) // TIM1 CH1
	#define LEFT_LIN_1 PAL_LINE(GPIOA,7) // TIM1 CH1N
	#define LEFT_LIN_2 PAL_LINE(GPIOA,9) // TIM1 CH2
	#define LEFT_HIN_2 PAL_LINE(GPIOB,0) // TIM1 CH2N

  #define RIGHT_HIN_1 PAL_LINE(GPIOA,8) // TIM1 CH3
  #define RIGHT_LIN_1 PAL_LINE(GPIOA,7) // TIM1 CH3N
  #define RIGHT_LIN_2 PAL_LINE(GPIOA,9) // TIM1 CH4
  #define RIGHT_HIN_2 PAL_LINE(GPIOB,0) // TIM1 CH4N

#endif

// *******************elbow driver pin config******************* //

// *******************encoder pin config******************* //

#define MISO_ENCODER PAL_LINE(GPIOC, 2)
#define CLK_ENCODER PAL_LINE(GPIOB, 13)
#define CS_LEFT_ENCODER PAL_LINE(GPIOC, 6)
#define CS_RIGHT_ENCODER PAL_LINE(GPIOC, 10)

// *******************encoder pin config******************* //

// ***************************PID coef************************** //

PID_t elbow_PID = {
  .coef = {.kp = 3500, .ki = 500, .kd = 0},
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

arm_encoder_t left_elbow_encoder =
{
  .encoder_ptr = &SPID2,
  .encoder_pins = {
    .cs_encoder = CS_LEFT_ENCODER,
    .clk_encoder = CLK_ENCODER,
    .miso_encoder = MISO_ENCODER
  },
  .encoder_conf = {
    .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
    .ssline = CS_LEFT_ENCODER,
    .end_cb = NULL
  }
};

arm_encoder_t right_elbow_encoder =
{
  .encoder_ptr = &SPID2,
  .encoder_pins = {
    .cs_encoder = CS_RIGHT_ENCODER,
    .clk_encoder = CLK_ENCODER,
    .miso_encoder = MISO_ENCODER
  },
  .encoder_conf = {
    .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
    .ssline = CS_RIGHT_ENCODER,
    .end_cb = NULL
  }
};

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
    .hin_1 = LEFT_PWM,
    .lin_2 = LEFT_DOWN,
    .lin_1 = LEFT_UP
	};

  const control_driver_t left_arm = {
    .line_control = left_control,
    .pwm_setting_ctx = left_pwm_ctx
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
    .hin_1 = RIGHT_PWM,
    .lin_2 = RIGHT_DOWN,
    .lin_1 = RIGHT_UP
	};

	const control_driver_t right_arm = {
    .line_control = right_control,
    .pwm_setting_ctx = right_pwm_ctx
	};

// ***********************right arm config*********************** //


#endif

#if(DRIVER == BB_DRIVER)

// ***********************left arm config*********************** //

	const pwm_channel_t ch_left_pwm = {
    .ch_pwm_1 = 0,
    .ch_pwm_2 = 1,
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

        {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// LEFT LIN1 & HIN1

        {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // LEFT HIN2 & LIN2

        {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// RIGHT LIN1 & HIN1

        {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // RIGHT LN2 & HIN2I

      },
      .cr2        = 0,
    // !!!!!!!! THE CALCULATION WAS MADE FOR F411 !!!!!!!! //
      .bdtr 		= 0b11111111,
    // !!!!!!!! THE CALCULATION WAS MADE FOR F411 !!!!!!!! //
      .dier       = 0
    }
	};

	const line_driver_t left_control = {
    .hin_1 = LEFT_HIN_1,
    .hin_2 = LEFT_HIN_2,
    .lin_1 = LEFT_LIN_1,
    .lin_2 = LEFT_LIN_2
	};

  const control_driver_t left_arm = {
    .line_control = left_control,
    .pwm_setting_ctx = left_pwm_ctx
  };

// ***********************left arm config*********************** //

// ***********************right arm config*********************** //

	const pwm_channel_t ch_right_pwm = {
    .ch_pwm_1 = 2,
    .ch_pwm_2 = 3,
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

      {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// LEFT LIN1 & HIN1

      {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // LEFT HIN2 & LIN2

      {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// RIGHT LIN1 & HIN1

      {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // RIGHT LN2 & HIN2I

      },
      .cr2        = 0,

    // !!!!!!!! THE CALCULATION WAS MADE FOR F411 !!!!!!!! //
      .bdtr 		= 0b11111111,
    // !!!!!!!! THE CALCULATION WAS MADE FOR F411 !!!!!!!! //

      .dier       = 0
    }
	};

	const line_driver_t right_control = {
    .hin_1 = RIGHT_HIN_1,
    .hin_2 = RIGHT_HIN_2,
    .lin_1 = RIGHT_LIN_1,
    .lin_2 = RIGHT_LIN_2
	};

	const control_driver_t right_arm = {
    .line_control = right_control,
    .pwm_setting_ctx = right_pwm_ctx
	};

// ***********************right arm config*********************** //

#endif

// ***********************final struct declaration*********************** //

traking_cs_t left_cs;
traking_cs_t right_cs;
arm_system_t right_system;
arm_system_t left_system;

arm_driver_ctx_t elbow_driver;

// ***********************final struct declaration*********************** //



/**
 * @details initialize elbow driver
 */
void elbow_init(void)
{
  // init left_cs struct
  left_cs.angle_lim = left_angle_lim;
  left_cs.angle_dead_zone = ENCODER_DEADZONE;
  left_cs.arm_PID = elbow_PID;
  left_cs.arm_encoder = left_elbow_encoder;

  // init right_system struct
  left_system.traking_cs = left_cs;
  left_system.control = left_arm;

  // init right_cs struct
  right_cs.angle_lim = right_angle_lim;
  right_cs.angle_dead_zone = ENCODER_DEADZONE;
  right_cs.arm_PID = elbow_PID;
  right_cs.arm_encoder = right_elbow_encoder;

  // init right_system struct
  right_system.traking_cs = right_cs;
  right_system.control = right_arm;

  // init final elbow_driver struct
  elbow_driver.type = DRIVER;
  elbow_driver.down = &elbow_down;
  elbow_driver.up = &elbow_up;
  elbow_driver.off = &elbow_off;
  elbow_driver.arm[0] = left_system;
  elbow_driver.arm[1] = right_system;

  driver_init(&elbow_driver);
  acs_init(&elbow_driver);
}


/**
 * @details the function controls the raising of the elbow up
 * @param[in] side - left or right side of hand
 * @param[in] period - PWM period
 */
void elbow_up(arm_side_t side, uint16_t period)
{
	arm_up(side, &elbow_driver, period);
}

/**
 * @details the function controls the raising of the elbow down
 * @param[in] side - left or right side of hand
 * @param[in] period - PWM period
 */
void elbow_down(arm_side_t side, uint16_t period)
{
	arm_down(side, &elbow_driver, period);
}

/**
 * @details the function disables the selected elbow
 * @param[in] side - left or right side of hand
 */
void elbow_off(arm_side_t side)
{
	arm_off(side, &elbow_driver);
}

/**
 * @details the function set input angle ~(0-40)
 * @param[in] side - left or right side of hand
 * @param[in] target_angle - setpoint angle
 */
void elbow_set_angle(float target_angle, arm_side_t side)
{
  acs_set_angle(target_angle, side, &elbow_driver);
}

/**
 * @details the function update current state of elbow
 * @param[in] dt - function call period
 */
void elbow_update_angle(float dt)
{
  acs_update_angle(dt, RIGHT, &elbow_driver);
  acs_update_angle(dt, LEFT, &elbow_driver);
}

/**
 * @details the function get encoder struct
 * @param[in] encoder_side - left of right encoder
 * @return encoder struct
 */
arm_encoder_t elbow_get_encoder_ctx(arm_side_t encoder_side)
{
  switch (encoder_side) {
    case LEFT:
      return left_elbow_encoder;
      break;
    case RIGHT:
      return right_elbow_encoder;
      break;
    default:
      break;
  }

}
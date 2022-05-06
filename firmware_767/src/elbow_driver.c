#include "elbow_driver.h"

// *******************elbow driver type config******************* //

#define BB_DRIVER       0
#define RED_DRIVER      1
#define DRIVER          RED_DRIVER

// *******************elbow driver type config******************* //

// *******************elbow driver PWM config******************* //

#define PWM_frequency		500000
#define PWM_period			10000

PWMDriver * const pwm1Driver = &PWMD1;

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

PWMDriver * const pwm8Driver = &PWMD8;

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

// *******************elbow driver PWM config******************* //


// **********************close sys config********************** //

#define ENCODER_DEADZONE 1

// **********************close sys config********************** //

// *******************elbow driver pin config******************* //

#if(DRIVER == RED_DRIVER)

// left elbow
#define LEFT_PWM_ELBOW         		PAL_LINE(GPIOE, 13) // TIM1 CH3 AF1
#define LEFT_UP_ELBOW          		PAL_LINE(GPIOB, 1)
#define LEFT_DOWN_ELBOW        		PAL_LINE(GPIOB, 15)

// left shoulder in
#define LEFT_PWM_SHOULDER_IN    	PAL_LINE(GPIOE, 9)  // TIM1_CH1 AF1
#define LEFT_UP_SHOULDER_IN     	PAL_LINE(GPIOC, 8)
#define LEFT_DOWN_SHOULDER_IN   	PAL_LINE(GPIOE, 14)

// left shoulder out
#define LEFT_PWM_SHOULDER_OUT    	PAL_LINE(GPIOE, 11) // TIM1_CH2 AF1
#define LEFT_UP_SHOULDER_OUT     	PAL_LINE(GPIOA, 5)
#define LEFT_DOWN_SHOULDER_OUT   	PAL_LINE(GPIOB, 0)

// right elbow
#define RIGHT_PWM_ELBOW        		PAL_LINE(GPIOC, 9)  // TIM8 CH4 AF3
#define RIGHT_UP_ELBOW         		PAL_LINE(GPIOD,13)
#define RIGHT_DOWN_ELBOW       		PAL_LINE(GPIOB,2)

// right shoulder in
#define RIGHT_PWM_SHOULDER_IN   	PAL_LINE(GPIOC, 6)  // TIM8_CH1 AF3
#define RIGHT_UP_SHOULDER_IN    	PAL_LINE(GPIOE, 10)
#define RIGHT_DOWN_SHOULDER_IN  	PAL_LINE(GPIOE, 12)

// right shoulder out
#define RIGHT_PWM_SHOULDER_OUT   	PAL_LINE(GPIOC, 7)  // TIM8_CH2 AF3
#define RIGHT_UP_SHOULDER_OUT    	PAL_LINE(GPIOD, 11)
#define RIGHT_DOWN_SHOULDER_OUT  	PAL_LINE(GPIOD, 12)

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
#define MISO_ENCODER_LEFT               PAL_LINE(GPIOA, 6)//SPI1
#define CLK_ENCODER_LEFT                PAL_LINE(GPIOB, 3)//SPI1
#define MISO_ENCODER_RIGHT			    PAL_LINE(GPIOC, 2)//SPI2
#define CLK_ENCODER_RIGHT 			    PAL_LINE(GPIOD, 3)//SPI2
#define CS_LEFT_ENCODER_ELBOW 			PAL_LINE(GPIOA, 3)
#define CS_RIGHT_ENCODER_ELBOW 			PAL_LINE(GPIOA, 4)
#define CS_LEFT_ENCODER_SHOULDER_IN 	PAL_LINE(GPIOC, 0)
#define CS_RIGHT_ENCODER_SHOULDER_IN 	PAL_LINE(GPIOG,0 )
#define CS_LEFT_ENCODER_SHOULDER_OUT 	PAL_LINE(GPIOG, 2)
#define CS_RIGHT_ENCODER_SHOULDER_OUT 	PAL_LINE(GPIOG, 3)
// *******************encoder pin config******************* //

// ***************************PID coef************************** //

const PID_t elbow_PID = {
  .coef = {.kp = 3500, .ki = 500, .kd = 0},
  .error = {.P = 0, .prev_P = 0, .I = 0, .D = 0}
};

const PID_t shoulder_in_PID = {
  .coef = {.kp = 6000, .ki = 500, .kd = 0},
  .error = {.P = 0, .prev_P = 0, .I = 0, .D = 0}
};

const PID_t shoulder_out_PID = {
  .coef = {.kp = 3500, .ki = 500, .kd = 0},
  .error = {.P = 0, .prev_P = 0, .I = 0, .D = 0}
};

// ***************************PID coef************************** //

// ***************************angle lim************************* //

const angle_lim_t right_angle_lim_elbow= {
  .max_angle = 62.6660,
  .min_angle = 22.9394
};

const angle_lim_t left_angle_lim_elbow = {
  .max_angle = 18.2812,
  .min_angle = 334.9511
};

const angle_lim_t right_angle_lim_shoulder_in = {
  .max_angle = 30.3222,
  .min_angle = 3329.5019
};

const angle_lim_t left_angle_lim_shoulder_in = {
  .max_angle = 325.8105, //min down
  .min_angle = 25.5761 //max up
};

const angle_lim_t right_angle_lim_shoulder_out = {
  .max_angle = 61.6123,
  .min_angle = 113.4667
};

const angle_lim_t left_angle_lim_shoulder_out = {
  .max_angle = 132.1875, //outside
  .min_angle = 78.7500 //inside
};

// ***************************angle lim************************** //


#if(DRIVER == RED_DRIVER)

// ***********************left arm config*********************** //

const pwm_channel_t ch_left_pwm_elbow = {
		.alt_func_1 = 1,
		.ch_pwm_1 = 2
	};

const pwm_channel_t ch_left_pwm_shoulder_in = {
	.alt_func_1 = 1,
	.ch_pwm_1 = 0
};

const pwm_channel_t ch_left_pwm_shoulder_out = {
	.alt_func_1 = 1,
	.ch_pwm_1 = 1
};

const pwm_ctx_t left_pwm_ctx_elbow = {
	.pwm_ch = ch_left_pwm_elbow,
	.driver_ptr = pwm1Driver,
	.pwm_conf = pwm1config
};

const pwm_ctx_t left_pwm_ctx_shoulder_in = {
	.pwm_ch = ch_left_pwm_shoulder_in,
	.driver_ptr = pwm1Driver,
	.pwm_conf = pwm1config,
};

const pwm_ctx_t left_pwm_ctx_shoulder_out = {
	.pwm_ch = ch_left_pwm_shoulder_out,
	.driver_ptr = pwm1Driver,
	.pwm_conf = pwm1config
};

const line_driver_t left_control_elbow = {
	.hin_1 = LEFT_PWM_ELBOW,
	.lin_2 = LEFT_DOWN_ELBOW,
	.lin_1 = LEFT_UP_ELBOW
};

const line_driver_t left_control_shoulder_in = {
	.hin_1 = LEFT_PWM_SHOULDER_IN,
	.lin_2 = LEFT_DOWN_SHOULDER_IN,
	.lin_1 = LEFT_UP_SHOULDER_IN
};

const line_driver_t left_control_shoulder_out = {
	.hin_1 = LEFT_PWM_SHOULDER_OUT,
	.lin_2 = LEFT_DOWN_SHOULDER_OUT,
	.lin_1 = LEFT_UP_SHOULDER_OUT
};

const control_driver_t left_arm_elbow = {
	.line_control = left_control_elbow,
	.pwm_setting_ctx = left_pwm_ctx_elbow
};

const control_driver_t left_arm_shoulder_in = {
	.line_control = left_control_shoulder_in,
	.pwm_setting_ctx = left_pwm_ctx_shoulder_in
};

const control_driver_t left_arm_shoulder_out = {
	.line_control = left_control_shoulder_out,
	.pwm_setting_ctx = left_pwm_ctx_shoulder_out
};


const arm_encoder_t left_elbow_encoder =
{
	.encoder_ptr = &SPID1,
	.encoder_pins = {
		.cs_encoder = CS_LEFT_ENCODER_ELBOW,
		.clk_encoder = CLK_ENCODER_LEFT,
		.miso_encoder = MISO_ENCODER_LEFT
	},
	.encoder_conf = {
		.cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
		.ssline = CS_LEFT_ENCODER_ELBOW,
		.end_cb = NULL
	}
};

const arm_encoder_t left_shoulder_in_encoder =
{
	.encoder_ptr = &SPID1,
	.encoder_pins = {
		.cs_encoder = CS_LEFT_ENCODER_SHOULDER_IN,
		.clk_encoder = CLK_ENCODER_LEFT,
		.miso_encoder = MISO_ENCODER_LEFT
	},
	.encoder_conf = {
		.cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
		.ssline = CS_LEFT_ENCODER_SHOULDER_IN,
		.end_cb = NULL
	}
};

const arm_encoder_t left_shoulder_out_encoder =
{
	.encoder_ptr = &SPID1,
	.encoder_pins = {
		.cs_encoder = CS_LEFT_ENCODER_SHOULDER_OUT,
		.clk_encoder = CLK_ENCODER_LEFT,
		.miso_encoder = MISO_ENCODER_LEFT
	},
	.encoder_conf = {
		.cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
		.ssline = CS_LEFT_ENCODER_SHOULDER_OUT,
		.end_cb = NULL
	}
};


// ***********************left arm config*********************** //


// ***********************right arm config*********************** //

const pwm_channel_t ch_right_pwm_elbow = {
	.alt_func_1 = 3,
	.ch_pwm_1 = 3
};

const pwm_channel_t ch_right_pwm_shoulder_in = {
	.alt_func_1 = 3,
	.ch_pwm_1 = 0
};

const pwm_channel_t ch_right_pwm_shoulder_out = {
	.alt_func_1 = 3,
	.ch_pwm_1 = 1
};

const pwm_ctx_t right_pwm_ctx_elbow = {
	.pwm_ch = ch_right_pwm_elbow,
	.driver_ptr = pwm8Driver,
	.pwm_conf = pwm8config
};

const pwm_ctx_t right_pwm_ctx_shoulder_in = {
	.pwm_ch = ch_right_pwm_shoulder_in,
	.driver_ptr = pwm8Driver,
	.pwm_conf = pwm8config
};

const pwm_ctx_t right_pwm_ctx_shoulder_out = {
	.pwm_ch = ch_right_pwm_shoulder_out,
	.driver_ptr = pwm8Driver,
	.pwm_conf = pwm8config
};

const line_driver_t right_control_elbow = {
	.hin_1 = RIGHT_PWM_ELBOW,
	.lin_2 = RIGHT_DOWN_ELBOW,
	.lin_1 = RIGHT_UP_ELBOW
};

const line_driver_t right_control_shoulder_in = {
	.hin_1 = RIGHT_PWM_SHOULDER_IN,
	.lin_2 = RIGHT_DOWN_SHOULDER_IN,
	.lin_1 = RIGHT_UP_SHOULDER_IN
};

const line_driver_t right_control_shoulder_out = {
	.hin_1 = RIGHT_PWM_SHOULDER_OUT,
	.lin_2 = RIGHT_DOWN_SHOULDER_OUT,
	.lin_1 = RIGHT_UP_SHOULDER_OUT
};

const control_driver_t right_arm_elbow = {
	.line_control = right_control_elbow,
	.pwm_setting_ctx = right_pwm_ctx_elbow
};

const control_driver_t right_arm_shoulder_in = {
	.line_control = right_control_shoulder_in,
	.pwm_setting_ctx = right_pwm_ctx_shoulder_in
};

const control_driver_t right_arm_shoulder_out = {
	.line_control = right_control_shoulder_out,
	.pwm_setting_ctx = right_pwm_ctx_shoulder_out
};

const arm_encoder_t right_elbow_encoder =
{
	.encoder_ptr = &SPID2,
	.encoder_pins = {
		.cs_encoder = CS_RIGHT_ENCODER_ELBOW,
		.clk_encoder = CLK_ENCODER_RIGHT,
		.miso_encoder = MISO_ENCODER_RIGHT
	},
	.encoder_conf = {
		.cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
		.ssline = CS_RIGHT_ENCODER_ELBOW,
		.end_cb = NULL
	}
};

const arm_encoder_t right_shoulder_in_encoder =
{
	.encoder_ptr = &SPID2,
	.encoder_pins = {
		.cs_encoder = CS_RIGHT_ENCODER_SHOULDER_IN,
		.clk_encoder = CLK_ENCODER_RIGHT,
		.miso_encoder = MISO_ENCODER_RIGHT
	},
	.encoder_conf = {
		.cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
		.ssline = CS_RIGHT_ENCODER_SHOULDER_IN,
		.end_cb = NULL
	}
};

const arm_encoder_t right_shoulder_out_encoder =
{
	.encoder_ptr = &SPID2,
	.encoder_pins = {
		.cs_encoder = CS_RIGHT_ENCODER_SHOULDER_OUT,
		.clk_encoder = CLK_ENCODER_RIGHT,
		.miso_encoder = MISO_ENCODER_RIGHT
	},
	.encoder_conf = {
		.cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
		.ssline = CS_RIGHT_ENCODER_SHOULDER_OUT,
		.end_cb = NULL
	}
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

// *** tracking structures for left arm *** //
const traking_cs_t left_cs_elbow = {
	.angle_lim = left_angle_lim_elbow,
	.angle_dead_zone = ENCODER_DEADZONE,
	.arm_PID = elbow_PID,
	.arm_encoder = left_elbow_encoder
};

const traking_cs_t left_cs_shoulder_in = {
	.angle_lim = left_angle_lim_shoulder_in,
	.angle_dead_zone = ENCODER_DEADZONE,
	.arm_PID = shoulder_in_PID,
	.arm_encoder = left_shoulder_in_encoder
};

const traking_cs_t left_cs_shoulder_out = {
	.angle_lim = left_angle_lim_shoulder_out,
	.angle_dead_zone = ENCODER_DEADZONE,
	.arm_PID = shoulder_out_PID,
	.arm_encoder = left_shoulder_out_encoder
};

// *** tracking structures for right arm *** //
traking_cs_t right_cs_elbow = {
	.angle_lim = right_angle_lim_elbow,
	.angle_dead_zone = ENCODER_DEADZONE,
	.arm_PID = elbow_PID,
	.arm_encoder = right_elbow_encoder
};

const traking_cs_t right_cs_shoulder_in = {
	.angle_lim = right_angle_lim_shoulder_in,
	.angle_dead_zone = ENCODER_DEADZONE,
	.arm_PID = shoulder_in_PID,
	.arm_encoder = right_shoulder_in_encoder
};


const traking_cs_t right_cs_shoulder_out = {
	.angle_lim = right_angle_lim_shoulder_out,
	.angle_dead_zone = ENCODER_DEADZONE,
	.arm_PID = shoulder_out_PID,
	.arm_encoder = right_shoulder_out_encoder
};

// structure for both arms
arm_driver_ctx_t arm_driver;


// ***********************final struct declaration*********************** //

void motor_init(
	arm_system_t *arm_system_out,
	const control_driver_t *control_driver,
	const traking_cs_t *tracking_driver
)
{
	arm_system_out->control = *control_driver;
	arm_system_out->traking_cs = *tracking_driver;
}


static bool isInitialized   = false;

/**
 * @details initialize elbow driver
 */
void elbow_init(void)
{
	if (isInitialized)
		return;

	arm_driver.type = DRIVER;
	arm_driver.down = &elbow_down;
	arm_driver.up = &elbow_up;
	arm_driver.off = &elbow_off;

	// left arm
	motor_init(&arm_driver.arm[0], &left_arm_elbow, 		&left_cs_elbow);
	motor_init(&arm_driver.arm[1], &left_arm_shoulder_in, 	&left_cs_shoulder_in);
	motor_init(&arm_driver.arm[2], &left_arm_shoulder_out,  &left_cs_shoulder_out);

	// right arm
	motor_init(&arm_driver.arm[3], &right_arm_elbow, 		&right_cs_elbow);
	motor_init(&arm_driver.arm[4], &right_arm_shoulder_in, 	&right_cs_shoulder_in);
	motor_init(&arm_driver.arm[5], &right_arm_shoulder_out, &right_cs_shoulder_out);

	driver_init(&arm_driver);
	acs_init(&arm_driver);
}


/**
 * @details the function controls the raising of the elbow up
 * @param[in] side - left or right side of hand
 * @param[in] period - PWM period
 */
void elbow_up(arm_side_t side, uint16_t period)
{
	arm_up(side, &arm_driver, period);
}

/**
 * @details the function controls the raising of the elbow down
 * @param[in] side - left or right side of hand
 * @param[in] period - PWM period
 */
void elbow_down(arm_side_t side, uint16_t period)
{
	arm_down(side, &arm_driver, period);
}

/**
 * @details the function disables the selected elbow
 * @param[in] side - left or right side of hand
 */
void elbow_off(arm_side_t side)
{
	arm_off(side, &arm_driver);
}

/**
 * @details the function set input angle ~(0-40)
 * @param[in] side - left or right side of hand
 * @param[in] target_angle - setpoint angle
 */
void elbow_set_angle(float target_angle, arm_side_t side)
{
  acs_set_angle(target_angle, side, &arm_driver);
}

/**
 * @details the function update current state of elbow
 * @param[in] dt - function call period
 */
void elbow_update_angle(float dt)
{
  acs_update_angle(dt, RIGHT_ELBOW, &arm_driver);
  acs_update_angle(dt, LEFT_ELBOW, &arm_driver);
  acs_update_angle(dt, RIGHT_SHOULDER_IN, &arm_driver);
  acs_update_angle(dt, LEFT_SHOULDER_IN, &arm_driver);
  acs_update_angle(dt, RIGHT_SHOULDER_OUT, &arm_driver);
  acs_update_angle(dt, LEFT_SHOULDER_OUT, &arm_driver);
}

/**
 * @details the function get encoder struct
 * @param[in] encoder_side - left of right encoder
 * @return encoder struct
 */
arm_encoder_t elbow_get_encoder_ctx(arm_side_t encoder_side)
{
    switch (encoder_side) {
        case LEFT_ELBOW:
            return left_elbow_encoder;
            break;
        case LEFT_SHOULDER_IN:
            return left_shoulder_in_encoder;
            break;
        case LEFT_SHOULDER_OUT:
            return left_shoulder_out_encoder;
            break;
        case  RIGHT_ELBOW:
            return right_elbow_encoder;
            break;
        case RIGHT_SHOULDER_IN:
            return right_shoulder_in_encoder;
            break;
        case RIGHT_SHOULDER_OUT:
            return right_shoulder_out_encoder;
            break;
        default:
            break;
    }
}
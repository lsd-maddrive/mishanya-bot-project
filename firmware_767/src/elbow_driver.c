#include "elbow_driver.h"


#define DRIVER RED

// *******************arm driver PWM config******************* //



// *******************arm driver PWM config******************* //


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
                        .end_cb = NULL
                }
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
                        .end_cb = NULL
                }
        };

// **********************close sys config********************** //

#define ENCODER_DEADZONE 1


// ***************************PID coef************************** //

const PID_t elbow_PID = {
  .coef = {.kp = 3500, .ki = 500, .kd = 0},
  .error = {.P = 0, .prev_P = 0, .I = 0, .D = 0}
};

// ***************************PID coef************************** //

// ***************************angle lim************************* //

const angle_lim_t right_angle_lim_elbow= {
  .max_angle = 62.6660F,
  .min_angle = 22.9394F
};

const angle_lim_t left_angle_lim_elbow = {
  .max_angle = 18.2812F,
  .min_angle = 334.9511F
};

// ***************************angle lim************************** //

arm_ctx_t elbow_driver;
/**
 * @details initialize arm driver
 */
void elbow_init(void)
{
	static bool isInitialized   = false;

	if (isInitialized)
		return;

  elbow_driver.arm[LEFT].traking_cs.arm_PID = elbow_PID;
  elbow_driver.arm[LEFT].traking_cs.arm_encoder = left_elbow_encoder;
  elbow_driver.arm[LEFT].arm_angle.angle_lim = left_angle_lim_elbow;
  elbow_driver.arm[LEFT].arm_angle.angle_dead_zone = ENCODER_DEADZONE;

  elbow_driver.arm[RIGHT].traking_cs.arm_PID = elbow_PID;
  elbow_driver.arm[RIGHT].traking_cs.arm_encoder = right_elbow_encoder;
  elbow_driver.arm[RIGHT].arm_angle.angle_lim = right_angle_lim_elbow;
  elbow_driver.arm[RIGHT].arm_angle.angle_dead_zone = ENCODER_DEADZONE;

  lld_red_init_driver(&elbow_driver.arm[LEFT].traking_cs.control,
                      LEFT_UP_ELBOW, LEFT_DOWN_ELBOW,
                      &PWMD1, LEFT_ELBOW_ALT_FUNC_NUM);

  lld_red_init_driver(&elbow_driver.arm[RIGHT].traking_cs.control,
                      RIGHT_UP_ELBOW, RIGHT_DOWN_ELBOW,
                      &PWMD8, RIGHT_ELBOW_ALT_FUNC_NUM);


  elbow_driver.type = DRIVER;
  elbow_driver.down = &elbow_down;
  elbow_driver.up = &elbow_up;
  elbow_driver.off = &elbow_off;

	acs_init(&elbow_driver);
}


/**
 * @details the function controls the raising of the arm up
 * @param[in] side - left or right side of hand
 * @param[in] period - PWM period
 */
void elbow_up(arm_side_t side, uint16_t period)
{
	arm_up(side, &elbow_driver, period);
}

/**
 * @details the function controls the raising of the arm down
 * @param[in] side - left or right side of hand
 * @param[in] period - PWM period
 */
void elbow_down(arm_side_t side, uint16_t period)
{
	arm_down(side, &elbow_driver, period);
}

/**
 * @details the function disables the selected arm
 * @param[in] side - left or right side of hand
 */
void elbow_off(arm_side_t side)
{
	arm_off(side, &elbow_driver);
}

/**
 * @details the function set input angle
 * @param[in] side - left or right side of hand
 * @param[in] target_angle - setpoint angle
 */
void elbow_set_angle(float target_angle, arm_side_t side)
{
  acs_set_angle(target_angle, side, elbow_driver.arm);
}

/**
 * @details the function update current state of arm
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

//arm_encoder_t elbow_get_encoder_ctx(arm_side_t encoder_side)
//{
//    switch (encoder_side) {
//        case LEFT:
//            return left_elbow_encoder;
//            break;
//        case RIGHT:
//            return right_elbow_encoder;
//            break;
//        default:
//        	break;
//    }
//}

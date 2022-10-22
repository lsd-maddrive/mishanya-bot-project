#include "vertical_shoulder_driver.h"

#define DRIVER RED
#define ENCODER_DEADZONE 1

#define PID_P 3500U
#define PID_I 500U
#define PID_D 0U

static PWMDriver *LEFT_V_SHOULDER_PWM_PTR = &PWMD1;
static PWMDriver *RIGHT_V_SHOULDER_PWM_PTR = &PWMD8;

static SPIDriver *LEFT_SPI = &SPID1;
static SPIDriver *RIGHT_SPI = &SPID2;

// ***************************angle lim************************* //

// todo necessary that the angles are recorded in flash memory during calibration

const angle_lim_t right_angle_lim_v_shoulder = {
  .max_angle = 30.1464f,
  .min_angle = 329.3261f
};

const angle_lim_t left_angle_lim_v_shoulder = {
  .max_angle = 132.1875f,
  .min_angle = 78.7500f
};

// ***************************angle lim************************** //

arm_ctx_t v_shoulder_driver;
/**
 * @details initialize arm driver
 */
void v_shoulder_init(void)
{
  static bool isInitialized   = false;

  if (isInitialized)
    return;

  PID_set_coef(&v_shoulder_driver.arm[RIGHT].traking_cs.arm_PID, PID_P, PID_D, PID_I);
  v_shoulder_driver.arm[LEFT].arm_angle.angle_lim = left_angle_lim_v_shoulder;
  v_shoulder_driver.arm[LEFT].arm_angle.angle_dead_zone = ENCODER_DEADZONE;

  PID_set_coef(&v_shoulder_driver.arm[RIGHT].traking_cs.arm_PID, PID_P, PID_D, PID_I);
  v_shoulder_driver.arm[RIGHT].arm_angle.angle_lim = right_angle_lim_v_shoulder;
  v_shoulder_driver.arm[RIGHT].arm_angle.angle_dead_zone = ENCODER_DEADZONE;

  lld_red_init_driver(&v_shoulder_driver.arm[LEFT].traking_cs.control,
                      LEFT_UP_V_SHOULDER, LEFT_DOWN_V_SHOULDER,
                      LEFT_V_SHOULDER_PWM_PTR, LEFT_PWM_V_SHOULDER_CH_NUM);

  lld_red_init_driver(&v_shoulder_driver.arm[RIGHT].traking_cs.control,
                      RIGHT_UP_V_SHOULDER, RIGHT_DOWN_V_SHOULDER,
                      RIGHT_V_SHOULDER_PWM_PTR, RIGHT_PWM_V_SHOULDER_CH_NUM);


  encoder_init(&v_shoulder_driver.arm[LEFT].traking_cs.arm_encoder,
               CS_LEFT_ENCODER_V_SHOULDER, CLK_ENCODER_LEFT, MISO_ENCODER_LEFT,
               LEFT_SPI);


  encoder_init(&v_shoulder_driver.arm[RIGHT].traking_cs.arm_encoder,
               CS_RIGHT_ENCODER_V_SHOULDER, CLK_ENCODER_RIGHT, MISO_ENCODER_RIGHT,
               RIGHT_SPI);

  v_shoulder_driver.type = DRIVER;
  v_shoulder_driver.down = &v_shoulder_down;
  v_shoulder_driver.up = &v_shoulder_up;
  v_shoulder_driver.off = &v_shoulder_off;

  acs_init(&v_shoulder_driver);
}


/**
 * @details the function controls the raising of the arm up
 * @param[in] side - left or right side of hand
 * @param[in] period - PWM period
 */
void v_shoulder_up(arm_side_t side, uint16_t period)
{
  arm_up(side, &v_shoulder_driver, period);
}

/**
 * @details the function controls the raising of the arm down
 * @param[in] side - left or right side of hand
 * @param[in] period - PWM period
 */
void v_shoulder_down(arm_side_t side, uint16_t period)
{
  arm_down(side, &v_shoulder_driver, period);
}

/**
 * @details the function disables the selected arm
 * @param[in] side - left or right side of hand
 */
void v_shoulder_off(arm_side_t side)
{
  arm_off(side, &v_shoulder_driver);
}

/**
 * @details the function set input angle
 * @param[in] side - left or right side of hand
 * @param[in] target_angle - setpoint angle
 */
void v_shoulder_set_angle(float target_angle, arm_side_t side)
{
  acs_set_angle(target_angle, side, v_shoulder_driver.arm);
}

/**
 * @details the function reads the angle of the horizontal shoulder
 * @param[in] side - left or right side of hand
 */
float v_shoulder_read_angle(arm_side_t side)
{
  return encoder_read(&v_shoulder_driver.arm[side].traking_cs.arm_encoder);
}

/**
 * @details the function update current state of arm
 * @param[in] dt - function call period
 */
void v_shoulder_update_angle(float dt)
{
  acs_update_angle(dt, RIGHT, &v_shoulder_driver);
  acs_update_angle(dt, LEFT, &v_shoulder_driver);
}


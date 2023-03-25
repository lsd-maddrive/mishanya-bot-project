#include "elbow_driver.h"

#define DRIVER RED
#define ENCODER_DEADZONE 1U

// elbow
#define GLOBAL_MIN_ANGLE 46
#define GLOBAL_MAX_ANGLE 86

#define PID_P 6000U
#define PID_I 500U
#define PID_D 0U

static PWMDriver *LEFT_ELBOW_PWM_PTR = &PWMD1;
static PWMDriver *RIGHT_ELBOW_PWM_PTR = &PWMD8;

static SPIDriver *LEFT_SPI = &SPID1;
static SPIDriver *RIGHT_SPI = &SPID2;

joint_t elbow_driver;
/**
 * @details initialize arm driver
 */
void elbow_init(void)
{
	static bool is_init   = false;

	if(is_init)
  {
    return;
  }


  PID_set_coef(&elbow_driver.arm[LEFT].traking_cs.arm_PID, (float)PID_P, (float)PID_D, (float)PID_I);
  memcpy(&elbow_driver.arm[LEFT].arm_angle.local_angle_lim.min_angle,
         (uint32_t *)LEFT_DOWN_ELBOW_ADDRESS, sizeof(float));
  memcpy(&elbow_driver.arm[LEFT].arm_angle.local_angle_lim.max_angle,
         (uint32_t *)LEFT_UP_ELBOW_ADDRESS, sizeof(float));

//  if(elbow_driver.arm[LEFT].arm_angle.local_angle_lim.min_angle < elbow_driver.arm[LEFT].arm_angle.local_angle_lim.max_angle)
//  {
//      elbow_driver.arm[LEFT].arm_angle.local_angle_lim.min_angle -= 0.5f;
//      elbow_driver.arm[LEFT].arm_angle.local_angle_lim.max_angle += 0.5f;
//  }
//  else
//  {
//      elbow_driver.arm[LEFT].arm_angle.local_angle_lim.min_angle += 0.5f;
//      elbow_driver.arm[LEFT].arm_angle.local_angle_lim.max_angle -= 0.5f;
//  }



  elbow_driver.arm[LEFT].arm_angle.angle_dead_zone = ENCODER_DEADZONE;

  PID_set_coef(&elbow_driver.arm[RIGHT].traking_cs.arm_PID, (float)PID_P, (float)PID_D, (float)PID_I);
  memcpy(&elbow_driver.arm[RIGHT].arm_angle.local_angle_lim.min_angle,
         (uint32_t *)RIGHT_DOWN_ELBOW_ADDRESS, sizeof(float));
  memcpy(&elbow_driver.arm[RIGHT].arm_angle.local_angle_lim.max_angle,
         (uint32_t *)RIGHT_UP_ELBOW_ADDRESS, sizeof(float));

//    if(elbow_driver.arm[RIGHT].arm_angle.local_angle_lim.min_angle < elbow_driver.arm[RIGHT].arm_angle.local_angle_lim.max_angle)
//    {
//        elbow_driver.arm[RIGHT].arm_angle.local_angle_lim.min_angle -= 0.5f;
//        elbow_driver.arm[RIGHT].arm_angle.local_angle_lim.max_angle += 0.5f;
//    }
//    else
//    {
//        elbow_driver.arm[RIGHT].arm_angle.local_angle_lim.min_angle += 0.5f;
//        elbow_driver.arm[RIGHT].arm_angle.local_angle_lim.max_angle -= 0.5f;
//    }

  elbow_driver.arm[RIGHT].arm_angle.angle_dead_zone = ENCODER_DEADZONE;

  lld_red_init_driver(&elbow_driver.arm[LEFT].traking_cs.control,
                      LEFT_UP_ELBOW, LEFT_DOWN_ELBOW,
                      LEFT_ELBOW_PWM_PTR, LEFT_PWM_ELBOW_CH_NUM);

  lld_red_init_driver(&elbow_driver.arm[RIGHT].traking_cs.control,
                      RIGHT_UP_ELBOW, RIGHT_DOWN_ELBOW,
                      RIGHT_ELBOW_PWM_PTR, RIGHT_PWM_ELBOW_CH_NUM);


  encoder_init(&elbow_driver.arm[LEFT].traking_cs.arm_encoder,
               CS_LEFT_ENCODER_ELBOW, CLK_ENCODER_LEFT, MISO_ENCODER_LEFT,
               LEFT_SPI);


  encoder_init(&elbow_driver.arm[RIGHT].traking_cs.arm_encoder,
               CS_RIGHT_ENCODER_ELBOW, CLK_ENCODER_RIGHT, MISO_ENCODER_RIGHT,
               RIGHT_SPI);

  elbow_driver.type = DRIVER;
  elbow_driver.down = &elbow_down;
  elbow_driver.up = &elbow_up;
  elbow_driver.off = &elbow_off;
  elbow_driver.global_angle_lim.min_angle = GLOBAL_MIN_ANGLE;
  elbow_driver.global_angle_lim.max_angle = GLOBAL_MAX_ANGLE;
  elbow_driver.working_interval = GLOBAL_MAX_ANGLE - GLOBAL_MIN_ANGLE;

	acs_init(&elbow_driver);

  is_init = true;
}


/**
 * @details the function controls the raising of the arm up
 * @param[in] side - left or right side of hand
 * @param[in] period - PWM period
 */
void elbow_up(arm_side_t side, uint16_t period)
{
  joint_up(side, &elbow_driver, period);
}

/**
 * @details the function controls the raising of the arm down
 * @param[in] side - left or right side of hand
 * @param[in] period - PWM period
 */
void elbow_down(arm_side_t side, uint16_t period)
{
  joint_down(side, &elbow_driver, period);
}

/**
 * @details the function disables the selected arm
 * @param[in] side - left or right side of hand
 */
void elbow_off(arm_side_t side)
{
  joint_off(side, &elbow_driver);
}

/**
 * @details the function reads the angle of the elbow
 * @param[in] side - left or right side of hand
 */
float elbow_read_angle(arm_side_t side)
{
  return encoder_read(&elbow_driver.arm[side].traking_cs.arm_encoder);
}

/**
 * @details the function set input angle
 * @param[in] side - left or right side of hand
 * @param[in] target_angle - setpoint angle
 */
void elbow_set_angle(float target_angle, arm_side_t side)
{
  acs_set_angle(target_angle, side, elbow_driver.arm, &elbow_driver.global_angle_lim, elbow_driver.working_interval);
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

bool elbow_get_status(arm_side_t side)
{
  return elbow_driver.arm[side].arm_angle.target_angle.reach_target_angle;
}

angle_lim_t* elbow_get_global_angle_lim(void)
{
  return &elbow_driver.global_angle_lim;
}
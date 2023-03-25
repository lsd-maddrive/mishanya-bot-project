#include "horizontal_shoulder_driver.h"

#define DRIVER RED
#define ENCODER_DEADZONE 1U

// horizontal shoulder
#define GLOBAL_MIN_ANGLE -5
#define GLOBAL_MAX_ANGLE 47

#define PID_P 6000U
#define PID_I 500U
#define PID_D 0U

static PWMDriver *LEFT_H_SHOULDER_PWM_PTR = &PWMD1;
static PWMDriver *RIGHT_H_SHOULDER_PWM_PTR = &PWMD8;

static SPIDriver *LEFT_SPI = &SPID1;
static SPIDriver *RIGHT_SPI = &SPID2;


joint_t h_shoulder_driver;
/**
 * @details initialize arm driver
 */
void h_shoulder_init(void)
{
  static bool is_init   = false;

  if (is_init)
  {
    return;
  }

  PID_set_coef(&h_shoulder_driver.arm[LEFT].traking_cs.arm_PID, (float)PID_P, (float)PID_D, (float)PID_I);
  memcpy(&h_shoulder_driver.arm[LEFT].arm_angle.local_angle_lim.min_angle,
         (uint32_t *)LEFT_DOWN_H_SHOULDER_ADDRESS, sizeof(float));
  memcpy(&h_shoulder_driver.arm[LEFT].arm_angle.local_angle_lim.max_angle,
         (uint32_t *)LEFT_UP_H_SHOULDER_ADDRESS, sizeof(float));


//    if(h_shoulder_driver.arm[LEFT].arm_angle.local_angle_lim.min_angle
//       < h_shoulder_driver.arm[LEFT].arm_angle.local_angle_lim.max_angle)
//    {
//        h_shoulder_driver.arm[LEFT].arm_angle.local_angle_lim.min_angle -= 0.5f;
//        h_shoulder_driver.arm[LEFT].arm_angle.local_angle_lim.max_angle += 0.5f;
//    }
//    else
//    {
//        h_shoulder_driver.arm[LEFT].arm_angle.local_angle_lim.min_angle += 0.5f;
//        h_shoulder_driver.arm[LEFT].arm_angle.local_angle_lim.max_angle -= 0.5f;
//    }

  h_shoulder_driver.arm[LEFT].arm_angle.angle_dead_zone = ENCODER_DEADZONE;

  PID_set_coef(&h_shoulder_driver.arm[RIGHT].traking_cs.arm_PID, (float)PID_P, (float)PID_D, (float)PID_I);
  memcpy(&h_shoulder_driver.arm[RIGHT].arm_angle.local_angle_lim.min_angle,
         (uint32_t *)RIGHT_DOWN_H_SHOULDER_ADDRESS, sizeof(float));
  memcpy(&h_shoulder_driver.arm[RIGHT].arm_angle.local_angle_lim.max_angle,
         (uint32_t *)RIGHT_UP_H_SHOULDER_ADDRESS, sizeof(float));

//    if(h_shoulder_driver.arm[RIGHT].arm_angle.local_angle_lim.min_angle
//            < h_shoulder_driver.arm[RIGHT].arm_angle.local_angle_lim.max_angle)
//    {
//        h_shoulder_driver.arm[RIGHT].arm_angle.local_angle_lim.min_angle -= 0.5f;
//        h_shoulder_driver.arm[RIGHT].arm_angle.local_angle_lim.max_angle += 0.5f;
//    }
//    else
//    {
//        h_shoulder_driver.arm[RIGHT].arm_angle.local_angle_lim.min_angle += 0.5f;
//        h_shoulder_driver.arm[RIGHT].arm_angle.local_angle_lim.max_angle -= 0.5f;
//    }

  h_shoulder_driver.arm[RIGHT].arm_angle.angle_dead_zone = ENCODER_DEADZONE;

  lld_red_init_driver(&h_shoulder_driver.arm[LEFT].traking_cs.control,
                      LEFT_UP_H_SHOULDER, LEFT_DOWN_H_SHOULDER,
                      LEFT_H_SHOULDER_PWM_PTR, LEFT_PWM_H_SHOULDER_CH_NUM);

  lld_red_init_driver(&h_shoulder_driver.arm[RIGHT].traking_cs.control,
                      RIGHT_UP_H_SHOULDER, RIGHT_DOWN_H_SHOULDER,
                      RIGHT_H_SHOULDER_PWM_PTR, RIGHT_PWM_H_SHOULDER_CH_NUM);


  encoder_init(&h_shoulder_driver.arm[LEFT].traking_cs.arm_encoder,
               CS_LEFT_ENCODER_H_SHOULDER, CLK_ENCODER_LEFT, MISO_ENCODER_LEFT,
               LEFT_SPI);


  encoder_init(&h_shoulder_driver.arm[RIGHT].traking_cs.arm_encoder,
               CS_RIGHT_ENCODER_H_SHOULDER, CLK_ENCODER_RIGHT, MISO_ENCODER_RIGHT,
               RIGHT_SPI);

  h_shoulder_driver.type = DRIVER;
  h_shoulder_driver.down = &h_shoulder_down;
  h_shoulder_driver.up = &h_shoulder_up;
  h_shoulder_driver.off = &h_shoulder_off;
  h_shoulder_driver.global_angle_lim.min_angle = GLOBAL_MIN_ANGLE;
  h_shoulder_driver.global_angle_lim.max_angle = GLOBAL_MAX_ANGLE;
  h_shoulder_driver.working_interval = GLOBAL_MAX_ANGLE - GLOBAL_MIN_ANGLE;

  acs_init(&h_shoulder_driver);

  is_init = true;
}


/**
 * @details the function controls the raising of the arm up
 * @param[in] side - left or right side of hand
 * @param[in] period - PWM period
 */
void h_shoulder_up(arm_side_t side, uint16_t period)
{
  joint_up(side, &h_shoulder_driver, period);
}

/**
 * @details the function controls the raising of the arm down
 * @param[in] side - left or right side of hand
 * @param[in] period - PWM period
 */
void h_shoulder_down(arm_side_t side, uint16_t period)
{
  joint_down(side, &h_shoulder_driver, period);
}

/**
 * @details the function disables the selected arm
 * @param[in] side - left or right side of hand
 */
void h_shoulder_off(arm_side_t side)
{
  joint_off(side, &h_shoulder_driver);
}

/**
 * @details the function set input angle
 * @param[in] side - left or right side of hand
 * @param[in] target_angle - setpoint angle
 */
void h_shoulder_set_angle(float target_angle, arm_side_t side)
{
  acs_set_angle(target_angle, side, h_shoulder_driver.arm, &h_shoulder_driver.global_angle_lim, h_shoulder_driver.working_interval);
}

/**
 * @details the function reads the angle of the horizontal shoulder
 * @param[in] side - left or right side of hand
 */
float h_shoulder_read_angle(arm_side_t side)
{
  return encoder_read(&h_shoulder_driver.arm[side].traking_cs.arm_encoder);
}

/**
 * @details the function update current state of arm
 * @param[in] dt - function call period
 */
void h_shoulder_update_angle(float dt)
{
  acs_update_angle(dt, RIGHT, &h_shoulder_driver);
  acs_update_angle(dt, LEFT, &h_shoulder_driver);
}


bool h_shoulder_get_status(arm_side_t side)
{
  return h_shoulder_driver.arm[side].arm_angle.target_angle.reach_target_angle;
}

angle_lim_t* h_shoulder_get_global_angle_lim(void)
{
  return &h_shoulder_driver.global_angle_lim;
}
#ifndef INCLUDE_LLD_CONTROL_SERVO_H_
#define INCLUDE_LLD_CONTROL_SERVO_H_

#include <common.h>

/**
 *  @brief structure for servos in arm
 *  @identifier1 pwm channel number
 *  @identifier2 PAL_LINE(GPIOx,pin)
 *  @identifier3 servo limit on the left in hand/wrist
 *  @identifier4 servo limit on the right in hand/wrist
 */
typedef struct
{
  uint8_t channel;
  ioline_t line;
  uint16_t left_hand_limit;
  uint16_t right_hand_limit;

} servo_arm;

/**
 *  @servo in the left hand
 */
static const servo_arm left_hand =
{
      .channel = 0,
      .line = PAL_LINE(GPIOE,9),
      .left_hand_limit = 1110,
      .right_hand_limit = 1620
};

/**
 *  @servo in the left wrist
 */
static const servo_arm left_wrist =
{
      .channel = 1,
      .line = PAL_LINE(GPIOE, 11),
      .left_hand_limit = 900,
      .right_hand_limit = 2100
};
/**
 *  @servo in the right hand
 */
static const servo_arm right_hand =
{
      .channel = 2,
      .line = PAL_LINE(GPIOE, 13),
      .left_hand_limit = 1110,
      .right_hand_limit = 1620
};

/**
 *  @servo in the right wrist
 */
static const servo_arm right_wrist =
{
      .channel = 3,
      .line = PAL_LINE(GPIOE, 14),
      .left_hand_limit = 900,
      .right_hand_limit = 2100
};

/**
 *  @brief Initialize PWM and pin
 *  @note variable init for protection
 *  @arg PAL_LINE(GPIOx,pin)
 */
void lld_control_servo_init(ioline_t line);

/**
 * @brief Set raw duty cycle for servo in hand
 * @args duty_cycle is raw value, left_limit is servo limit on the left,
 *  right_limit is servo limit on the right, channel is pwm channel number
 */
void lld_control_servo_hand(int16_t duty_cycle, uint16_t left_limit,
                            uint16_t right_limit, uint8_t channel);
#endif

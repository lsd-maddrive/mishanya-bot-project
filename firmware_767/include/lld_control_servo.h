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

extern servo_arm left_hand;
extern servo_arm left_wrist;
extern servo_arm right_hand;
extern servo_arm right_wrist;
/**
 *  @brief Initialize PWM and pin
 *  @note variable init for protection
 */
void lld_control_servo_init(void);

/**
 * @brief Set raw duty cycle for servo in hand
 * @args duty_cycle is raw value,
 * servo is pointer to struct left/right_hand/wrist
 */
void lld_control_servo_hand(int16_t duty_cycle, servo_arm *servo);
#endif

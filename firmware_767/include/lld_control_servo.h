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
  uint16_t low_hand_limit;
  uint16_t high_hand_limit;

} servo_arm;

/**
 *  @brief Initialize PWM and pin
 *  @note variable init for protection
 */
void lld_control_servo_init(void);

/**
 * @brief Set raw duty cycle for servo
 * @args duty_cycle is raw value,
 * servo is pointer to struct left/right_hand/wrist
 */
void lld_control_servo(int16_t duty_cycle, servo_arm *servo);

/**
 * @brief Set raw duty cycle for servo
 * @args duty_cycle is raw value,
 * servo_t is a variable from the enum type_servo
 */
void lld_set_dutycycle_servo(int16_t duty_cycle, type_servo servo_t);

/**
 * @brief get high limit of the servo
 * @args servo_t is a variable from the enum type_servo
 * @return high limit of the servo
 */
uint16_t get_servo_high_limit(type_servo servo_t);

/**
 * @brief get low limit of the servo
 * @args servo_t is a variable from the enum type_servo
 * @return low limit of the servo
 */
uint16_t get_servo_low_limit(type_servo servo_t);

#endif

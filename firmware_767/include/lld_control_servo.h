#ifndef INCLUDE_LLD_CONTROL_SERVO_H_
#define INCLUDE_LLD_CONTROL_SERVO_H_

#include <common.h>

/*============================================================================*/
/* LIMITS FOR SERVO                                                           */
/*============================================================================*/
#define LEFT_SERVO_HAND 1110
#define RIGHT_SERVO_HAND 1620
#define LEFT_SERVO_WRIST 900
#define RIGHT_SERVO_WRIST 2100

/**
 *  @brief Initialize PWM and pin
 *  @note variable init for protection
 */
void lld_control_servo_init(void);
/**
 * @brief Set raw duty cycle for servo in wrist
 * @args duty_cycle is raw value
 */
void lld_control_servo_wrist(int16_t duty_cycle);
/**
 * @brief Set raw duty cycle for servo in hand
 * @args duty_cycle is raw value
 */
void lld_control_servo_hand(int16_t duty_cycle);

#endif

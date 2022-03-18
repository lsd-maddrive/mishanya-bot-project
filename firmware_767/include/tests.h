#ifndef INCLUDE_TEST_H
#define INCLUDE_TEST_H

#include <lld_control_servo.h>

/*
 * @brief Test of servos
 * @note value raw duty cycle
 * @args servo is pointer to struct left/right_hand/wrist
 */
void test_lld_servo(type_servo servo);
/*
 * @brief measurement of the non-linearity of the servo
 * @args servo is pointer to struct left/right_hand/wrist
 */
void test_lld_nonlinear(type_servo servo);
/*
 * @brief Test of bb_driver
 */
void test_lld_bb(void);
#endif

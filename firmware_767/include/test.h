#ifndef INCLUDE_TEST_H
#define INCLUDE_TEST_H

#include <common.h>
#include <lld_control_servo.h>

/*
 * @brief Test servo
 * @note value raw duty cycle
 * @args servo is pointer to struct left/right_hand/wrist
 */
void test_lld_servo_left_hand(servo_arm *servo);


#endif

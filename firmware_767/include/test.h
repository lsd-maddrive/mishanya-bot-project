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
 * @brief test forward and inverse Kinematics by computing on the controller
 * @note there is a unit of measurement conversion in the code
 */
void test_arm_kinematic(void);

#endif

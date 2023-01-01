#ifndef INCLUDE_TEST_H
#define INCLUDE_TEST_H

#include <lld_control_servo.h>
#include <arm_encoder.h>
#include <elbow_driver.h>
#include <arm_encoder.h>

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

/************* Elbow tests *************/

/**
 * @brief Test arm driver
 */
void test_arm_high_function(void);

/*********** Close sys tests ***********/

/**
 * @brief Test close system
 */
void test_arm_control_system(void);

/**
 * @brief test PID
 */
void test_PID(void);

/************ Encoder tests ************/

/**
 * @brief Test absolute encoder
 */
void test_arm_encoder(void);
/**
 * @brief Test close system
 * @note three angles are set for all parts of the hand
 */

void test_arm_kinematic (void);

#endif

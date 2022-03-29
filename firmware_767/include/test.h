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

/************* Elbow tests *************/

/**
 * @brief Test arm driver
 */
void test_elbow(void);

/*********** Close sys tests ***********/

/**
 * @brief Test close system
 */
void test_arm_control_system(void);

/**
 * @brief reset PID
 */
void test_PID(void);

/************ Encoder tests ************/

/**
 * @brief Test absolute encoder
 */
void test_abs_encoder(void);

#endif

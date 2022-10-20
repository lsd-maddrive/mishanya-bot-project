#ifndef INCLUDE_TEST_H
#define INCLUDE_TEST_H

#include <encoder_base.h>
#include "motor.h"

/**
 * @testing the all encoders
 * @note variable of encoder displayed in Serial
 */
void test_encoder_base_all(void);

/**
 * @testing the encoder
 * @note variable of encoder displayed in Serial
 * @args encoder is value from enum
 */
void test_encoder_base(type_encoder encoder);

/**
 * @brief test odometry to get distance, speed
 * @args encoder is value from enum
 */
void testOdometryBase(type_encoder encoder);

/**
 * @brief test odometry to get distance, speed all wheels
 * @args encoder is value from enum
 */
void testOdometryBaseAll(void);

/**
 * @brief Test for motor without feedback
 * @note duty_sycle is raw value
 * @args motor_n is value from enum
 */
void testlldMotor(type_motor motor_n);

/**
 * @brief Test for motors without feedback
 * @note duty_sycle is raw value
 * @args motor_n is value from enum
 */
void testlldMotorAll(void);

/**
 * @brief Test for motor without feedback
 * @note duty_sycle is is the percentage value
 * @args motor_n is value from enum
 */
void testlldMotorPer(type_motor motor_n);

/**
 * @brief Test for motors without feedback
 * @note duty_sycle is is the percentage value
 * @args motor_n is value from enum
 */
void testlldMotorPerAll(void);

#endif
#ifndef INCLUDE_TEST_H
#define INCLUDE_TEST_H

#include <encoder_base.h>

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
 */
void testOdometryBase(void);

/**
 * @brief test odometry to get distance, speed all wheels
 */
void testOdometryBaseAll(void);

#endif

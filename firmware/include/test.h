#ifndef INCLUDE_TEST_H
#define INCLUDE_TEST_H

#include <common.h>
#include "arm_encoder.h"
#include "elbow_driver.h"



/************ Encoder tests ************/

/**
 * @brief Test absolute encoder
 */
void test_elbow_encoder(arm_side_t encoder_side);


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
 * @brief Test normalize interval and angle
 */
void test_normalize(void);


/**
 * @brief reset PID
 */
void test_PID(void);

#endif

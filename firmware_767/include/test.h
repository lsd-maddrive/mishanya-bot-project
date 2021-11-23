#ifndef INCLUDE_TEST_H
#define INCLUDE_TEST_H

#include <common.h>

/*
 * @brief Test servo in left hand
 * @note value raw duty cycle
 */
void test_lld_servo_left_hand(void);
/*
 * @brief Test servo in right hand
 * @note value raw duty cycle
 */
void test_lld_servo_right_hand(void);
/*
 * @brief Test servo in left wrist
 * @note value raw duty cycle
 */
void test_lld_servo_left_wrist(void);
/*
 * @brief Test servo in right wrist
 * @note value raw duty cycle
 */
void test_lld_servo_right_wrist(void);

#endif

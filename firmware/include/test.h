#ifndef INCLUDE_TEST_H
#define INCLUDE_TEST_H

#include <common.h>



/************ Encoder tests ************/

/**
 * @brief Test absolute encoder
 */
void test_abs_encoder(void);


/************* Elbow tests *************/

/**
 * @brief Test arm driver
 */
void test_elbow(void);


/*********** Close sys tests ***********/

/**
 * @brief Test close system
 */
void test_close_sys(void);

/**
 * @brief Test normalize interval and angle
 */
void test_normalize(void);

/*********** lld tests ***********/

/**
 * @brief Test lld bb driver
 */
void test_lld_bb(void);

/**
 * @brief Test lld red driver
 */
void test_lld_red(void);

/*********** lld tests ***********/

/**
 * @brief reset PID
 */
void test_PID(void);

#endif

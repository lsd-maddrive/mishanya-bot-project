#ifndef INCLUDE_ARM_DRIVER_H
#define INCLUDE_ARM_DRIVER_H

#include <common.h>

#define PWM1_frequency	500000
#define PWM1_period		10000

typedef enum {
	LEFT = 0,
	RIGHT = 1
} ARM_SIDE_t;


typedef enum {
	BB = 0,
	RED = 1
} DRIVER_t;

typedef struct {
	PWMDriver 		*driver_ptr;
	PWMConfig 		pwm_conf;
	bool 			is_started;
} pwm_ctx_t;

typedef struct {
	DRIVER_t 		type;
	pwm_ctx_t		*pwm_ctx;
	channels_side_t ch_side;
	arm_t			pins;
} driver_ctx_t;


typedef struct {
	uint8_t ch1_pwm;
	uint8_t ch2_pwm;
	ioline_t up;
	ioline_t down;
	ioline_t PWM_1;
	ioline_t PWM_2;
} arm_t;

typedef struct {
	uint8_t bit_OUTPUT;
	uint8_t bit_PUSHPULL;
	uint8_t bit_ALTERNATE;
	uint8_t bit_ALTERNATE_N;
} PAL_STM32_bits;

typedef struct {
	PAL_STM32_bits right1_pwm;
	PAL_STM32_bits right2_pwm;
	PAL_STM32_bits left1_pwm;
	PAL_STM32_bits left2_pwm;
} init_pwm_t;

typedef struct {
	PAL_STM32_bits left_down;
	PAL_STM32_bits left_up;
	PAL_STM32_bits right_down;
	PAL_STM32_bits right_up;
} init_digital_t;

typedef struct {
	init_pwm_t pwm_mode;
	init_digital_t digital_mode;
	arm_t left_arm;
	arm_t right_arm;
	PWMConfig pwm_conf;
} init_driver_t;


/**
 * @brief   Initialize arm driver
 */
void ARM_DRIVER_init(const init_driver_t init);

/**
 * @brief recieve the hand number and the filling period
 * the function controls the raising of the hand up
 */
void ARM_up(arm_t ARM, uint16_t PWM_period);

/**
 * @brief recieve the hand number and the filling period
 * the function controls the raising of the hand down
 */
void ARM_down(arm_t ARM, uint16_t PWM_period);

/**
 * @brief recieve the hand number
 * the function disables the selected hand
 */
void Off_ARM (arm_t ARM);

void test_new_driver(arm_t ARM, uint16_t PWM_period);

#endif

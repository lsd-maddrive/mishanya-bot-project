#ifndef INCLUDE_ARM_DRIVER_H
#define INCLUDE_ARM_DRIVER_H

#include <common.h>
#include <PID.h>

// *******************arm driver PWM config******************* //

#define ARM_FREQUENCY		500000
#define ARM_PERIOD			10000

// *******************arm driver PWM config******************* //

typedef enum {
	LEFT = 0,
	RIGHT = 1
} arm_side_t;

typedef enum {
	BB = 0,
	RED = 1
} driver_t;

typedef struct {
	uint8_t ch_pwm_1;
	uint8_t ch_pwm_2;
	uint8_t alt_func_1;
	uint8_t alt_func_2;
} pwm_channel_t;

typedef struct {
	PWMDriver 		*driver_ptr;
	PWMConfig 		pwm_conf;
	pwm_channel_t   pwm_ch;
} pwm_ctx_t;

typedef struct {
	ioline_t 			digit_1;
	ioline_t 			digit_2;
	ioline_t 			PWM_1;
	ioline_t 			PWM_2;
} line_driver_t;


typedef struct {
	float min_angle;
	float max_angle;
} angle_lim_t;


typedef struct{
	pwm_ctx_t 			arm_ctx;
	line_driver_t 		line_control;
	angle_lim_t			angle_lim;
} control_driver_t;


typedef struct {
	driver_t 			type;
	void (* up) (arm_side_t, uint16_t);
	void (* down) (arm_side_t, uint16_t);
	void (* off) (arm_side_t);
	control_driver_t	arm[];
} arm_driver_ctx_t;




void driver_init(const arm_driver_ctx_t *arm_driver);
void arm_up(arm_side_t side, const arm_driver_ctx_t *arm_driver, uint16_t period);
void arm_down(arm_side_t side, const arm_driver_ctx_t *arm_driver, uint16_t period);
void arm_off (arm_side_t side, const arm_driver_ctx_t *arm_driver);


#endif

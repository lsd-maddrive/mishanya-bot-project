#ifndef INCLUDE_ARM_DRIVER_H
#define INCLUDE_ARM_DRIVER_H

#include <common.h>


#define PWM_frequency	500000
#define PWM_period		10000

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
	ioline_t up;
	ioline_t down;
	ioline_t PWM_1;
	ioline_t PWM_2;
} control_driver_t;

typedef struct{
	pwm_ctx_t arm_ctx;
	control_driver_t arm_control;
} arm_t;

typedef struct {
	DRIVER_t 		type;
	arm_t			left;
	arm_t			right;
} driver_ctx_t;


void driver_init(driver_ctx_t *arm_driver);



#endif

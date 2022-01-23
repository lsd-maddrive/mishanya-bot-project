#ifndef INCLUDE_ARM_DRIVER_H
#define INCLUDE_ARM_DRIVER_H

#include <common.h>


#define PWM_FREQUENCY	500000
#define PWM_PERIOD		10000

typedef enum {
	LEFT = 0,
	RIGHT = 1
} arm_side_t;

typedef enum {
	BB = 0,
	RED = 1
} driver_t;

typedef struct {
	PWMDriver 		*driver_ptr;
	PWMConfig 		pwm_conf;
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
	driver_t 		type;
	arm_t			arm[];
} driver_ctx_t;


void driver_init(const driver_ctx_t *arm_driver);
void arm_up(arm_side_t side, const driver_ctx_t *arm_driver, uint16_t period);


#endif

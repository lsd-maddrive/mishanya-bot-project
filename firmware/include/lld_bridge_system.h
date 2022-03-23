#ifndef FIRMWARE_LLD_BRIDGE_SYSTEM_H
#define FIRMWARE_LLD_BRIDGE_SYSTEM_H

#include <common.h>

typedef struct {
    uint8_t           ch_pwm_1;					          // PWM first channel number
    uint8_t           ch_pwm_2;					          // PWM second channel number
    uint8_t           alt_func_1;					        // PWM first channel alternative function number
    uint8_t           alt_func_2;					        // PWM second channel alternative function number
} pwm_channel_t;

typedef struct {
    PWMDriver 		    *driver_ptr;	              // PWM pointer
    PWMConfig 		    pwm_conf;			              // PWM struct conf
    pwm_channel_t     pwm_ch;			                // typedef (search for description in this file)
} pwm_ctx_t;

typedef struct {
    ioline_t 			    digit_1;		                // first digit pin
    ioline_t 			    digit_2;		                // second digit pin
    ioline_t 			    PWM_1;			                // first PWM pin
    ioline_t 			    PWM_2;			                // second digit pin
} line_driver_t;

typedef struct{
    pwm_ctx_t 			  arm_ctx;		                  // typedef (search for description in this file)
    line_driver_t 	  line_control;	                // typedef (search for description in this file)
} control_driver_t;

#endif //FIRMWARE_LLD_BRIDGE_SYSTEM_H

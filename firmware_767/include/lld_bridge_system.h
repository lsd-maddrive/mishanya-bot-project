#ifndef FIRMWARE_LLD_BRIDGE_SYSTEM_H
#define FIRMWARE_LLD_BRIDGE_SYSTEM_H

#include <common.h>

typedef struct
{
    uint8_t           ch_pwm_1;	// PWM first channel number
    uint8_t           ch_pwm_2;	// PWM second channel number
    uint8_t           alt_func_1; // PWM first channel alternative function number
    uint8_t           alt_func_2; // PWM second channel alternative function number
    PWMDriver         *driver_ptr; // TIM pointer
} pwm_channel_t;

typedef struct {
    PWMConfig 		    pwm_conf; // PWM struct configuration
} pwm_ctx_t;

typedef struct {
    ioline_t 			    digit_1; // first digit pin
    ioline_t 			    digit_2; // second digit pin
    ioline_t 			    PWM_1;	// first PWM pin
    ioline_t 			    PWM_2;	// second PWM pin
} line_driver_t;

typedef struct{
    pwm_channel_t     pwm_setting_ctx; // struct with inform about PWM config
    line_driver_t line_control;	// struct with inform about pin
} control_driver_t;

#endif

#ifndef INCLUDE_ARM_DRIVER_H
#define INCLUDE_ARM_DRIVER_H

#include <common.h>


typedef enum {
	LEFT = 0,							                        // left hand
	RIGHT = 1							                        // right hand
} arm_side_t;

typedef enum {
    BB = 0,								                      // this type of driver requires two channel PWM
	RED = 1								                        // this type of driver requires one channel of PWM
} driver_t;

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

typedef struct {
  float min_angle;                               // min angle encored read
  float max_angle;                               // max angle encored read
} angle_lim_t;

typedef struct{
	pwm_ctx_t 			  arm_ctx;		                  // typedef (search for description in this file)
	line_driver_t 	  line_control;	                // typedef (search for description in this file)
  angle_lim_t			angle_lim;                      // typedef angle limit
} control_driver_t;

typedef struct {
    driver_t type;                                 // typedef (search for description in this file)
    void (* up) (arm_side_t, uint16_t);            // ptr function up
    void (* down) (arm_side_t, uint16_t);          // ptr function down
    void (* off) (arm_side_t);                     // ptr function off arm
    control_driver_t arm[];			                   // array because there is a right hand and a left hand
} arm_driver_ctx_t;


void driver_init(const arm_driver_ctx_t *arm_driver);
void arm_up(arm_side_t side, const arm_driver_ctx_t *arm_driver, uint16_t period);
void arm_down(arm_side_t side, const arm_driver_ctx_t *arm_driver, uint16_t period);
void arm_off (arm_side_t side, const arm_driver_ctx_t *arm_driver);


#endif

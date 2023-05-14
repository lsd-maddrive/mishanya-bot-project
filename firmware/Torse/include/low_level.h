//
// Created by Anton on 09.09.2022.
//

#ifndef ARM_LOW_LEVEL_H
#define ARM_LOW_LEVEL_H

#include "common.h"

#define LEFT_MOTOR_ALT_FUNC_NUM  1
#define RIGHT_MOTOR_ALT_FUNC_NUM 3

#define LEFT_SERVO_ALT_FUNC_NUM  2
#define RIGHT_SERVO_ALT_FUNC_NUM 2

#define SPI_ALT_FUNC_NUM       5


// *******************arm driver pin config******************* //

// left elbow
#define LEFT_PWM_ELBOW         		PAL_LINE(GPIOE, 13) // TIM1 CH3 AF1
#define LEFT_UP_ELBOW          		PAL_LINE(GPIOB, 1)
#define LEFT_DOWN_ELBOW        		PAL_LINE(GPIOB, 15)
#define LEFT_PWM_ELBOW_CH_NUM     2U

// right elbow
#define RIGHT_PWM_ELBOW        		PAL_LINE(GPIOC, 9)  // TIM8 CH4 AF3
#define RIGHT_UP_ELBOW         		PAL_LINE(GPIOD,13)
#define RIGHT_DOWN_ELBOW       		PAL_LINE(GPIOB,2)
#define RIGHT_PWM_ELBOW_CH_NUM    3U

// left vertical shoulder
#define LEFT_PWM_V_SHOULDER    	  PAL_LINE(GPIOE, 9)  // TIM1_CH1 AF1
#define LEFT_UP_V_SHOULDER     	  PAL_LINE(GPIOC, 8)
#define LEFT_DOWN_V_SHOULDER   	  PAL_LINE(GPIOE, 14)
#define LEFT_PWM_V_SHOULDER_CH_NUM     0U

// right vertical shoulder
#define RIGHT_PWM_V_SHOULDER   	  PAL_LINE(GPIOC, 6)  // TIM8_CH1 AF3
#define RIGHT_UP_V_SHOULDER    	  PAL_LINE(GPIOE, 10)
#define RIGHT_DOWN_V_SHOULDER  	  PAL_LINE(GPIOE, 12)
#define RIGHT_PWM_V_SHOULDER_CH_NUM     0U

// left horizontal shoulder
#define LEFT_PWM_H_SHOULDER    	  PAL_LINE(GPIOE, 11) // TIM1_CH2 AF1
#define LEFT_UP_H_SHOULDER     	  PAL_LINE(GPIOA, 5)
#define LEFT_DOWN_H_SHOULDER   	  PAL_LINE(GPIOB, 0)
#define LEFT_PWM_H_SHOULDER_CH_NUM     1U

// right horizontal shoulder
#define RIGHT_PWM_H_SHOULDER   	  PAL_LINE(GPIOC, 7)  // TIM8_CH2 AF3
#define RIGHT_UP_H_SHOULDER    	  PAL_LINE(GPIOD, 11)
#define RIGHT_DOWN_H_SHOULDER  	  PAL_LINE(GPIOD, 12)
#define RIGHT_PWM_H_SHOULDER_CH_NUM     1U

// right capture
#define RIGHT_CAPTURE   	        PAL_LINE(GPIOE, 6)
#define LEFT_CAPTURE    	        PAL_LINE(GPIOE, 5)

// *******************arm driver pin config******************* //

// *******************encoder pin config******************* //

#define MISO_ENCODER_LEFT          PAL_LINE(GPIOA, 6)//SPI1
#define CLK_ENCODER_LEFT           PAL_LINE(GPIOB, 3)//SPI1
#define MISO_ENCODER_RIGHT		     PAL_LINE(GPIOC, 2)//SPI2
#define CLK_ENCODER_RIGHT 		     PAL_LINE(GPIOD, 3)//SPI2

#define CS_LEFT_ENCODER_ELBOW 	    PAL_LINE(GPIOA, 3)
#define CS_RIGHT_ENCODER_ELBOW 	    PAL_LINE(GPIOA, 4)
#define CS_LEFT_ENCODER_V_SHOULDER 	PAL_LINE(GPIOC, 0)
#define CS_RIGHT_ENCODER_V_SHOULDER PAL_LINE(GPIOG, 0)
#define CS_LEFT_ENCODER_H_SHOULDER 	PAL_LINE(GPIOG, 2)
#define CS_RIGHT_ENCODER_H_SHOULDER PAL_LINE(GPIOG, 3)

// *******************encoder pin config******************* //

// *******************uart config******************* //
#define SERIAL_TX                    PAL_LINE(GPIOD, 8)
#define SERIAL_RX                    PAL_LINE(GPIOD, 9)

#define RADIO_TX                     PAL_LINE(GPIOD, 5)
#define RADIO_RX                     PAL_LINE(GPIOD, 6)
// *******************uart config******************* //

// *******************servo config******************* //
#define LEFT_GRIP                   PAL_LINE(GPIOB,6)
#define LEFT_GRIP_CH_NUM            0
#define LEFT_WRIST                  PAL_LINE(GPIOB,8)
#define LEFT_WRIST_CH_NUM           2
#define RIGHT_GRIP                  PAL_LINE(GPIOB,9)
#define RIGHT_GRIP_CH_NUM           3
#define RIGHT_WRIST                 PAL_LINE(GPIOB,5)
#define RIGHT_WRIST_CH_NUM          1
// *******************servo config******************* //


void init_low_level(void);
uint32_t low_level_get_tcp_address(void);

#endif //ARM_LOW_LEVEL_H

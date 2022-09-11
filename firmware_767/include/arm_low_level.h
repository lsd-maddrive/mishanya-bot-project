//
// Created by Anton on 09.09.2022.
//

#ifndef ARM_LOW_LEVEL_H
#define ARM_LOW_LEVEL_H

#include "common.h"
#include "part_arm_driver.h"
#include "arm_control_system.h"

// *******************arm driver pin config******************* //

// left elbow
#define LEFT_PWM_ELBOW         		PAL_LINE(GPIOE, 13) // TIM1 CH3 AF1
#define LEFT_UP_ELBOW          		PAL_LINE(GPIOB, 1)
#define LEFT_DOWN_ELBOW        		PAL_LINE(GPIOB, 15)

// left shoulder in
#define LEFT_PWM_SHOULDER_IN    	PAL_LINE(GPIOE, 9)  // TIM1_CH1 AF1
#define LEFT_UP_SHOULDER_IN     	PAL_LINE(GPIOC, 8)
#define LEFT_DOWN_SHOULDER_IN   	PAL_LINE(GPIOE, 14)

// left shoulder out
#define LEFT_PWM_SHOULDER_OUT    	PAL_LINE(GPIOE, 11) // TIM1_CH2 AF1
#define LEFT_UP_SHOULDER_OUT     	PAL_LINE(GPIOA, 5)
#define LEFT_DOWN_SHOULDER_OUT   	PAL_LINE(GPIOB, 0)

// right elbow
#define RIGHT_PWM_ELBOW        		PAL_LINE(GPIOC, 9)  // TIM8 CH4 AF3
#define RIGHT_UP_ELBOW         		PAL_LINE(GPIOD,13)
#define RIGHT_DOWN_ELBOW       		PAL_LINE(GPIOB,2)

// right shoulder in
#define RIGHT_PWM_SHOULDER_IN   	PAL_LINE(GPIOC, 6)  // TIM8_CH1 AF3
#define RIGHT_UP_SHOULDER_IN    	PAL_LINE(GPIOE, 10)
#define RIGHT_DOWN_SHOULDER_IN  	PAL_LINE(GPIOE, 12)

// right shoulder out
#define RIGHT_PWM_SHOULDER_OUT   	PAL_LINE(GPIOC, 7)  // TIM8_CH2 AF3
#define RIGHT_UP_SHOULDER_OUT    	PAL_LINE(GPIOD, 11)
#define RIGHT_DOWN_SHOULDER_OUT  	PAL_LINE(GPIOD, 12)

// *******************arm driver pin config******************* //

// *******************encoder pin config******************* //

#define MISO_ENCODER_LEFT               PAL_LINE(GPIOA, 6)//SPI1
#define CLK_ENCODER_LEFT                PAL_LINE(GPIOB, 3)//SPI1
#define MISO_ENCODER_RIGHT			        PAL_LINE(GPIOC, 2)//SPI2
#define CLK_ENCODER_RIGHT 			        PAL_LINE(GPIOD, 3)//SPI2
#define CS_LEFT_ENCODER_ELBOW 			    PAL_LINE(GPIOA, 3)
#define CS_RIGHT_ENCODER_ELBOW 			    PAL_LINE(GPIOA, 4)
#define CS_LEFT_ENCODER_SHOULDER_IN 	  PAL_LINE(GPIOC, 0)
#define CS_RIGHT_ENCODER_SHOULDER_IN 	  PAL_LINE(GPIOG,0 )
#define CS_LEFT_ENCODER_SHOULDER_OUT 	  PAL_LINE(GPIOG, 2)
#define CS_RIGHT_ENCODER_SHOULDER_OUT 	PAL_LINE(GPIOG, 3)

// *******************encoder pin config******************* //


#endif //ARM_LOW_LEVEL_H

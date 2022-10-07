#ifndef INCLUDE_ARM_DRIVER_H
#define INCLUDE_ARM_DRIVER_H

#include "common.h"
#include "lld_bridge_system.h"

typedef enum {
	LEFT = 0,							                        // left hand
	RIGHT = 1							                        // right hand
} arm_side_t;

typedef enum {
  BB = 0,								                        // this type of driver requires two channel PWM
	RED = 1								                        // this type of driver requires one channel of PWM
} driver_t;


typedef struct {
  float min_angle;                               // min angle encored read
  float max_angle;                               // max angle encored read
} angle_lim_t;


typedef struct {
	angle_lim_t			  angle_lim;                    // typedef angle limit
	uint8_t 					angle_dead_zone;							// deadzone of encoder
	uint16_t					dt;														// integration step
} close_conf_t;

typedef struct{
  close_conf_t      close_conf;
  control_driver_t  control;
} arm_system_t;

typedef struct {
  driver_t type;                                  // typedef (search for description in this file)
	void (* up) (arm_side_t, uint16_t);             // ptr function up
  void (* down) (arm_side_t, uint16_t);           // ptr function down
  void (* off) (arm_side_t);                      // ptr function off arm
  arm_system_t arm[];			                        // array because there is a right hand and a left hand
} arm_driver_ctx_t;


void driver_init(const arm_driver_ctx_t *arm_driver);
void arm_up(arm_side_t side, const arm_driver_ctx_t *arm_driver, uint16_t period);
void arm_down(arm_side_t side, const arm_driver_ctx_t *arm_driver, uint16_t period);
void arm_off (arm_side_t side, const arm_driver_ctx_t *arm_driver);


#endif

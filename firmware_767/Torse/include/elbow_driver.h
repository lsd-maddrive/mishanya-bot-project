#ifndef INCLUDE_ELBOW_DRIVER_H
#define INCLUDE_ELBOW_DRIVER_H

#include "common.h"
#include "PID.h"
#include "part_arm_driver.h"
#include "arm_control_system.h"


void elbow_init(void);
void elbow_up(arm_side_t side, uint16_t period);
void elbow_down(arm_side_t side, uint16_t period);
void elbow_off(arm_side_t side);
void elbow_set_angle(float target_angle, arm_side_t side);
void elbow_update_angle(float dt);
arm_encoder_t elbow_get_encoder_ctx(arm_side_t encoder_side);


#endif

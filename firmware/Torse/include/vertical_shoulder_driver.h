//
// Created by Anton on 09.09.2022.
//

#ifndef VERTICAL_SHOULDER_DRIVER_H
#define VERTICAL_SHOULDER_DRIVER_H


#include "common.h"
#include "PID.h"
#include "joint.h"
#include "arm_control_system.h"


void v_shoulder_init(void);
void v_shoulder_up(arm_side_t side, uint16_t period);
void v_shoulder_down(arm_side_t side, uint16_t period);
void v_shoulder_off(arm_side_t side);
void v_shoulder_set_angle(float target_angle, arm_side_t side);
void v_shoulder_update_angle(float dt);
float v_shoulder_read_angle(arm_side_t side);
bool v_shoulder_get_status(arm_side_t side);

#endif //VERTICAL_SHOULDER_DRIVER_H

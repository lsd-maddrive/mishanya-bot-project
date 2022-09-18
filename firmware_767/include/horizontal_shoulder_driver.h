//
// Created by Anton on 09.09.2022.
//

#ifndef HORIZONTAL_SHOULDER_DRIVER_H
#define HORIZONTAL_SHOULDER_DRIVER_H


#include "common.h"
#include "PID.h"
#include "part_arm_driver.h"
#include "arm_control_system.h"


void h_shoulder_init(void);
void h_shoulder_up(arm_side_t side, uint16_t period);
void h_shoulder_down(arm_side_t side, uint16_t period);
void h_shoulder_off(arm_side_t side);
void h_shoulder_set_angle(float target_angle, arm_side_t side);
void h_shoulder_update_angle(float dt);

#endif //HORIZONTAL_SHOULDER_DRIVER_H

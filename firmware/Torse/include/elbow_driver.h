#ifndef INCLUDE_ELBOW_DRIVER_H
#define INCLUDE_ELBOW_DRIVER_H

#include "common.h"
#include "PID.h"
#include "joint.h"
#include "arm_control_system.h"
#include "string.h"
#include "arm_calibration.h"

void elbow_init(void);
void elbow_up(arm_side_t side, uint16_t period);
void elbow_down(arm_side_t side, uint16_t period);
void elbow_off(arm_side_t side);
void elbow_set_angle(float target_angle, arm_side_t side);
void elbow_update_angle(float dt);
float elbow_read_angle(arm_side_t side);
bool elbow_get_status(arm_side_t side);
angle_lim_t* elbow_get_global_angle_lim(void);


#endif

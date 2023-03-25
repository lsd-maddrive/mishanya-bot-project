#ifndef INCLUDE_ARM_CONTROL_SYSTEM_H
#define INCLUDE_ARM_CONTROL_SYSTEM_H

#include "common.h"
#include "arm_encoder.h"
#include "joint.h"
#include "PID.h"
#include "macro_lib.h"

void acs_init(joint_t* joint);
void acs_update_angle(float dt, arm_side_t side, joint_t *joint);
void acs_set_angle(float target_angle, arm_side_t side, arm_info_t *arm_driver, angle_lim_t* global_angle_lim, float working_interval);

#endif

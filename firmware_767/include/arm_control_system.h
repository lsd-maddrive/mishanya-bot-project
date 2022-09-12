#ifndef INCLUDE_ARM_CONTROL_SYSTEM_H
#define INCLUDE_ARM_CONTROL_SYSTEM_H

#include "common.h"
#include "arm_encoder.h"
#include "part_arm_driver.h"
#include "robo_lib/PID.h"

void acs_init(arm_ctx_t* elbow_driver);
void acs_update_angle(float dt, arm_side_t side, arm_ctx_t *arm_driver);
void acs_set_angle(float target_angle, arm_side_t side, arm_info_t *arm_driver);

#endif

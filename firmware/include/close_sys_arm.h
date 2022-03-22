#ifndef INCLUDE_CLOSE_ARM_SYS__H
#define INCLUDE_CLOSE_ARM_SYS__H

#include <common.h>
#include <encoder.h>
#include <arm_driver.h>
#include <serial.h>
#include <PID.h>
#include <stdbool.h>

void init_traking_cs(arm_driver_ctx_t* arm_driver);
void update_angle(float dt, arm_side_t side, arm_driver_ctx_t *arm_driver);
void set_angle(float target_angle, arm_side_t side, arm_driver_ctx_t *arm_driver);

#endif

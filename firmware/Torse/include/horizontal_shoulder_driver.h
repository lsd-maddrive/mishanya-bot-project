//
// Created by Anton on 09.09.2022.
//

#ifndef HORIZONTAL_SHOULDER_DRIVER_H
#define HORIZONTAL_SHOULDER_DRIVER_H


#include "common.h"
#include "PID.h"
#include "joint.h"
#include "arm_control_system.h"
#include "string.h"
#include "arm_calibration.h"


void h_shoulder_init(PWMDriver* left_h_shoulder_pwm_ptr, PWMDriver* right_h_shoulder_pwm_ptr,
                     SPIDriver* left_h_shoulder_spi_ptr, SPIDriver* right_h_shoulder_spi_ptr);
void h_shoulder_up(arm_side_t side, uint16_t period);
void h_shoulder_down(arm_side_t side, uint16_t period);
void h_shoulder_off(arm_side_t side);
void h_shoulder_set_angle(float target_angle, arm_side_t side);
void h_shoulder_update_angle(float dt);
float h_shoulder_read_angle(arm_side_t side);
bool h_shoulder_get_status(arm_side_t side);
angle_lim_t* h_shoulder_get_global_angle_lim(void);


#endif //HORIZONTAL_SHOULDER_DRIVER_H

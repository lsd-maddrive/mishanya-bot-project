#ifndef TORSE_CONTROL_SYSTEM_HANDLER_H
#define TORSE_CONTROL_SYSTEM_HANDLER_H

#include "common.h"
#include "elbow_driver.h"
#include "horizontal_shoulder_driver.h"
#include "vertical_shoulder_driver.h"
#include "joint.h"
#include "arm_kinematic.h"

#define SHOULDER_LENGTH 0.258f
#define FOREARM_LENGTH 0.236f
#define BASE_COOR_X 0
#define BASE_COOR_Y 0
#define BASE_COOR_Z 0

void control_system_handler_init(void);
void control_system_handler_set_coordinates(arm_side_t side, coord_t* target_coordinates);

#endif //TORSE_CONTROL_SYSTEM_HANDLER_H

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

typedef enum
{
    COORD_SET = 0,
    COORD_NOT_SET = 1,
}coordinates_set_t;

void control_system_handler_init(void);
coordinates_set_t control_system_handler_set_coordinates(arm_side_t side, coord_t* target_coordinates);

#endif //TORSE_CONTROL_SYSTEM_HANDLER_H

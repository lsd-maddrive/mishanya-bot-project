#ifndef TORSE_ARMS_H
#define TORSE_ARMS_H

#include "common.h"
#include "joint.h"
#include "arm_kinematic.h"
#include "elbow_driver.h"
#include "horizontal_shoulder_driver.h"
#include "vertical_shoulder_driver.h"

#define SHOULDER_LENGTH 0.258f
#define FOREARM_LENGTH 0.236f
#define BASE_COOR_X 0
#define BASE_COOR_Y 0
#define BASE_COOR_Z 0

void arms_init(void);
void arm_set_coordinates(arm_side_t side, coord_t* target_coordinates);

#endif //TORSE_ARMS_H

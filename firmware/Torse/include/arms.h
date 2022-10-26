#ifndef TORSE_ARMS_H
#define TORSE_ARMS_H

#include "common.h"
#include "joint.h"
#include "arm_kinematic.h"
#include "elbow_driver.h"
#include "horizontal_shoulder_driver.h"
#include "vertical_shoulder_driver.h"


#define SHOULDER_LENGTH 0.3f
#define FOREARM_LENGTH 0.265f
#define BASE_COOR_X 0
#define BASE_COOR_Y 0
#define BASE_COOR_Z 0

typedef struct
{
  arm_kinematic_t kinematic;
  joint_t joints[3];
}arms_ctx_t;


void arms_init(void);
void arm_set_coordinates(arm_side_t side, coord_t* target_coordinates);

#endif //TORSE_ARMS_H

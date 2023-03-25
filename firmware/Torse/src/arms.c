#include "arms.h"

static arm_kinematic_t arm_kinematic;

void arms_init(void)
{
  elbow_init();
  v_shoulder_init();
  h_shoulder_init();

  arm_kinematic.arm_angle_limits.th1 = v_shoulder_get_global_angle_lim();
  arm_kinematic.arm_angle_limits.th2 = elbow_get_global_angle_lim();
  arm_kinematic.arm_angle_limits.th3 = h_shoulder_get_global_angle_lim();

  arm_kinematic.arm_length.forearm_length = FOREARM_LENGTH;
  arm_kinematic.arm_length.shoulder_length = SHOULDER_LENGTH;
  // todo change base coordinate
  arm_kinematic.coord_base.x = BASE_COOR_X;
  arm_kinematic.coord_base.y = BASE_COOR_Y;
  arm_kinematic.coord_base.z = BASE_COOR_Z;

}

void arm_set_coordinates(arm_side_t side, coord_t* target_coordinates)
{
  angles_t target_angles;
  if(arm_inverse_kinematic(&arm_kinematic, target_coordinates, &target_angles, side) == ERROR_NONE)
  {
    // update after transform
    v_shoulder_set_angle(target_angles.th1, side);
    elbow_set_angle(target_angles.th2, side);
    h_shoulder_set_angle(target_angles.th3, side);
  }
  else
  {
    return ;
  }

}
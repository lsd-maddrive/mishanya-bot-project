#include "arms.h"

static arm_kinematic_t arm_kinematic;

void arms_init(void)
{
  elbow_init();
  v_shoulder_init();
  h_shoulder_init();

  // vertical shoulder
  arm_kinematic.arm_angle_limits.th1.theta_min = -15;
  arm_kinematic.arm_angle_limits.th1.theta_max = 45;

  // elbow
  arm_kinematic.arm_angle_limits.th2.theta_min = 46;
  arm_kinematic.arm_angle_limits.th2.theta_max = 86;

  // horizontal shoulder
  arm_kinematic.arm_angle_limits.th3.theta_min = -5;
  arm_kinematic.arm_angle_limits.th3.theta_max = 47;

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
    // firstly we should transform angle from arm kinematics to arm control system
    target_angles.th1 = arm_kinematic.arm_angle_limits.th1.theta_max - target_angles.th1;
    target_angles.th2 = arm_kinematic.arm_angle_limits.th2.theta_max - target_angles.th2;
    target_angles.th3 = arm_kinematic.arm_angle_limits.th3.theta_max - target_angles.th3;

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
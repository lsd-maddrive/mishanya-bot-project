#include "arms.h"

static arm_kinematic_t arm_kinematic;

static THD_WORKING_AREA(arm_task,256);

static THD_FUNCTION(arm_task_update,arg) {
  (void) arg;
  systime_t time = chVTGetSystemTimeX();
  while (1) {
    elbow_update_angle(0.1f);
    v_shoulder_update_angle(0.1f);
    h_shoulder_update_angle(0.1f);
    time = chThdSleepUntilWindowed(time, TIME_MS2I(100)+time);
  }
}



void arms_init(void)
{
  elbow_init();
  v_shoulder_init();
  h_shoulder_init();

  chThdCreateStatic(arm_task,sizeof(arm_task),NORMALPRIO+1,
                    arm_task_update, NULL);

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
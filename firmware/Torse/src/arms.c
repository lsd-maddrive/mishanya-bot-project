#include "arms.h"
#include "serial.h"
static THD_WORKING_AREA(traking_elbow,256);
static THD_WORKING_AREA(traking_v_shoulder,256);
static THD_WORKING_AREA(traking_h_shoulder,256);

static THD_FUNCTION(elbow_update,arg) {
  (void) arg;
  systime_t time = chVTGetSystemTimeX();
  while (1) {
    elbow_update_angle(UPDATE_TIME_SEC);
    time = chThdSleepUntilWindowed(time, TIME_MS2I(UPDATE_TIME_MSEC)+time);
  }
}

static THD_FUNCTION(v_shoulder_update,arg) {
  (void) arg;
  systime_t time = chVTGetSystemTimeX();
  while (1) {
    v_shoulder_update_angle(UPDATE_TIME_SEC);
    time = chThdSleepUntilWindowed(time, TIME_MS2I(UPDATE_TIME_MSEC)+time);
  }
}

static THD_FUNCTION(h_shoulder_update,arg) {
  (void) arg;
  systime_t time = chVTGetSystemTimeX();
  while (1) {
    h_shoulder_update_angle(UPDATE_TIME_SEC);
    time = chThdSleepUntilWindowed(time, TIME_MS2I(UPDATE_TIME_MSEC)+time);
  }
}

arm_kinematic_t arm_kinematic;

void arms_init(void)
{
  chThdCreateStatic(traking_elbow,sizeof(traking_elbow),NORMALPRIO-2,
                    elbow_update, NULL);

  chThdCreateStatic(traking_v_shoulder,sizeof(traking_v_shoulder),NORMALPRIO-2,
                    v_shoulder_update, NULL);

  chThdCreateStatic(traking_h_shoulder,sizeof(traking_h_shoulder),NORMALPRIO-2,
                    h_shoulder_update, NULL);

  arm_kinematic.arm_length.forearm_length = FOREARM_LENGTH;
  arm_kinematic.arm_length.shoulder_length = SHOULDER_LENGTH;
  arm_kinematic.coord_base.x = BASE_COOR_X;
  arm_kinematic.coord_base.y = BASE_COOR_Y;
  arm_kinematic.coord_base.z = BASE_COOR_Z;

  // vertical shoulder
  arm_kinematic.arm_angle_limits.th1.theta_min = -17;
  arm_kinematic.arm_angle_limits.th1.theta_max = 45;

  // elbow
  arm_kinematic.arm_angle_limits.th2.theta_min = 46;
  arm_kinematic.arm_angle_limits.th2.theta_max = 86;

  // horizontal shoulder
  arm_kinematic.arm_angle_limits.th3.theta_min = -5;
  arm_kinematic.arm_angle_limits.th3.theta_max = 47;


  elbow_init();
  v_shoulder_init();
  h_shoulder_init();
}

void arm_set_coordinates(arm_side_t side, coord_t* target_coordinates)
{
  angles_t target_angles;
  if(arm_inverse_kinematic(&arm_kinematic, target_coordinates, &target_angles, side) == ERROR_NONE)
  {
    // firstly we should transform angle from arm kinematics to arm control system
    target_angles.th1 -= arm_kinematic.arm_angle_limits.th1.theta_min;
    target_angles.th2 -= arm_kinematic.arm_angle_limits.th2.theta_min;
    target_angles.th3 -= arm_kinematic.arm_angle_limits.th3.theta_min;

    dbgprintf("1=%.4f\r\n"
              "2=%.4f\r\n"
              "3=%.4f\r\n", target_angles.th1, target_angles.th2, target_angles.th3);
    // update after transform
//    h_shoulder_set_angle(target_angles.th1, side);
//    elbow_set_angle(target_angles.th2, side);
//    v_shoulder_set_angle(target_angles.th3, side);
  }
  else
  {
    dbgprintf("1=%.4f\r\n"
              "1=%.4f\r\n"
              "1=%.4f\r\n", 1.1f, 1.1f, 1.1f);
    return ;
  }

}
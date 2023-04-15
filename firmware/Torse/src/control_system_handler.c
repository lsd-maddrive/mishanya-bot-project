#include "control_system_handler.h"

static arm_kinematic_t arm_kinematic;
static THD_WORKING_AREA(control_system_task, 256);

static THD_FUNCTION(control_system_task_update,arg) {
    (void) arg;
    systime_t time = chVTGetSystemTimeX();
    while (1) {
        elbow_update_angle(0.1f);
        v_shoulder_update_angle(0.1f);
        h_shoulder_update_angle(0.1f);
        time = chThdSleepUntilWindowed(time, TIME_MS2I(100)+time);
    }
}

coordinates_set_t control_system_handler_set_coordinates(arm_side_t side, coord_t* target_coordinates)
{
    angles_t target_angles;
    if(arm_inverse_kinematic(&arm_kinematic, target_coordinates, &target_angles, side) == ERROR_NONE)
    {
        // update after transform
        v_shoulder_set_angle(target_angles.th1, side);
        elbow_set_angle(target_angles.th2, side);
        h_shoulder_set_angle(target_angles.th3, side);

        return COORD_SET;
    }
    else
    {
        return COORD_NOT_SET;
    }

}

void control_system_handler_init(void)
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

    chThdCreateStatic(control_system_task, sizeof(control_system_task), NORMALPRIO,
                      control_system_task_update, NULL);
}
#include "capture.h"
#include "servo_control_system.h"

static void ext_capture_right(void* args)
{
    args = (void*)args;
    servo_control_system_grip_update_state(RIGHT);
}

static void ext_capture_left(void* args)
{
    args = (void*)args;
    servo_control_system_grip_update_state(LEFT);
}

void capture_init(capture_t* capture, ioline_t right_capture, ioline_t left_capture)
{
    capture->capture_line[LEFT] = left_capture;
    capture->capture_line[RIGHT] = right_capture;

    palEnableLineEvent(left_capture, PAL_EVENT_MODE_BOTH_EDGES);
    palSetLineCallback(left_capture, ext_capture_left, NULL);

    palEnableLineEvent(right_capture, PAL_EVENT_MODE_BOTH_EDGES);
    palSetLineCallback(right_capture, ext_capture_right, NULL);
}



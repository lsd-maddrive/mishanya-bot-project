#include "arm_tasks.h"

static SerialDriver *uart_gui = &SD3;

static THD_WORKING_AREA(arm_task,256);
static THD_WORKING_AREA(gui_task,256);

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

static THD_FUNCTION(gui_task_update,arg) {
    (void) arg;
    uint8_t gui_buffer[255];
    systime_t time = chVTGetSystemTimeX();
    size_t read_size;
    static size_t msg_offset = 0;
    while (1) {
        read_size = sdReadI(uart_gui, (gui_buffer+msg_offset), 255);
        if(read_size > 0)
        {
            if(arm_proto_gui_parser(gui_buffer, (read_size + msg_offset)) == WAIT_MSG)
            {
                msg_offset += read_size;
            }
            else
            {
                msg_offset = 0;
            }
        }
        time = chThdSleepUntilWindowed(time, TIME_MS2I(100)+time);
    }
}


void arm_tasks_init(void)
{
    chThdCreateStatic(arm_task,sizeof(arm_task),NORMALPRIO+1,
                      arm_task_update, NULL);

    chThdCreateStatic(gui_task,sizeof(gui_task),NORMALPRIO+1,
                      gui_task_update, NULL);
}
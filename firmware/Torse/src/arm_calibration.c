#include "arm_calibration.h"

static void elbow_calibration(void);
static void v_shoulder_calibration(void);
static void h_shoulder_calibration(void);

void arm_calibration_start()
{
    elbow_calibration();
    v_shoulder_calibration();
    h_shoulder_calibration();
}

static void elbow_calibration(void)
{
    arm_side_t elbow_side = LEFT;
    float angle_speed = 0;
    float angle = 0;
    elbow_up(elbow_side, 5000);
    angle = elbow_read_angle(elbow_side);
    chThdSleepMilliseconds(10);
    while(1)
    {
        angle_speed = elbow_read_angle(elbow_side) - angle;
        if(angle_speed == 0)
        {
            flash_write_block(LEFT_UP_ELBOW_ADDRESS, (uint8_t*)&angle, 4);
            elbow_off(LEFT);
            break;
        }
        chThdSleepMilliseconds(10);
    }
}

static void v_shoulder_calibration(void)
{

}

static void h_shoulder_calibration(void)
{

}
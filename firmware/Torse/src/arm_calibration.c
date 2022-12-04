#include "arm_calibration.h"


typedef struct {
    void (*up) (arm_side_t, uint16_t);
    void (*down) (arm_side_t, uint16_t);
    void (*off) (arm_side_t);
    float (*read_encoder) (arm_side_t);
} control_arm_t;


void arm_calibration_start(void)
{
    float d_angle = 0;
    float angle = 0;
    control_arm_t arm_control[3];

    arm_control[ELBOW].down = elbow_down;
    arm_control[ELBOW].up = elbow_up;
    arm_control[ELBOW].off = elbow_off;
    arm_control[ELBOW].read_encoder = elbow_read_angle;

    arm_control[V_SHOULDER].down = v_shoulder_down;
    arm_control[V_SHOULDER].up = v_shoulder_up;
    arm_control[V_SHOULDER].off = v_shoulder_off;
    arm_control[V_SHOULDER].read_encoder = v_shoulder_read_angle;

    arm_control[H_SHOULDER].down = h_shoulder_down;
    arm_control[H_SHOULDER].up = h_shoulder_up;
    arm_control[H_SHOULDER].off = h_shoulder_off;
    arm_control[H_SHOULDER].read_encoder = h_shoulder_read_angle;

    for(size_t part_arm = 0; part_arm <= H_SHOULDER; part_arm++)
    {
        for(size_t side = 0; side <= RIGHT; side++)
        {
            arm_control[part_arm].up(side, 10000);
            angle = arm_control[part_arm].read_encoder(side);
            chThdSleepMilliseconds(1000);
            while(1)
            {
                d_angle = arm_control[part_arm].read_encoder(side) - angle;
                if(d_angle == 0)
                {
                    flash_write_block((BASE_CALIBRATION_ADDRESS + (part_arm+side)*ANGLE_SIZE), (uint8_t*)&angle, 4);
                    arm_control[part_arm].off(side);
                    break;
                }
                angle = arm_control[part_arm].read_encoder(side);
                chThdSleepMilliseconds(1000);
            }
        }
    }
}

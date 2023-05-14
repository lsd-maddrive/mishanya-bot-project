#include "arm_calibration.h"

typedef struct {
    void (*up) (arm_side_t, uint16_t);
    void (*down) (arm_side_t, uint16_t);
    void (*off) (arm_side_t);
    float (*read_encoder) (arm_side_t);
} control_arm_t;

static const uint32_t calibration_address[2*DEGREE_OF_FREEDOM_QTY*ARM_QTY] = {
    LEFT_UP_ELBOW_ADDRESS,
    LEFT_DOWN_ELBOW_ADDRESS,
    RIGHT_UP_ELBOW_ADDRESS,
    RIGHT_DOWN_ELBOW_ADDRESS,
    LEFT_UP_V_SHOULDER_ADDRESS,
    LEFT_DOWN_V_SHOULDER_ADDRESS,
    RIGHT_UP_V_SHOULDER_ADDRESS,
    RIGHT_DOWN_V_SHOULDER_ADDRESS,
    LEFT_UP_H_SHOULDER_ADDRESS,
    LEFT_DOWN_H_SHOULDER_ADDRESS,
    RIGHT_UP_H_SHOULDER_ADDRESS,
    RIGHT_DOWN_H_SHOULDER_ADDRESS
};

control_arm_t arm_control[DEGREE_OF_FREEDOM_QTY];

void calibration_init(void)
{
    arm_control[ELBOW].down = elbow_down;
    arm_control[ELBOW].up = elbow_up;
    arm_control[ELBOW].off = elbow_off;
    arm_control[ELBOW].read_encoder = elbow_read_angle;
    arm_control[ELBOW].off(LEFT);
    arm_control[ELBOW].off(RIGHT);

    arm_control[V_SHOULDER].down = v_shoulder_down;
    arm_control[V_SHOULDER].up = v_shoulder_up;
    arm_control[V_SHOULDER].off = v_shoulder_off;
    arm_control[V_SHOULDER].read_encoder = v_shoulder_read_angle;
    arm_control[V_SHOULDER].off(LEFT);
    arm_control[V_SHOULDER].off(RIGHT);

    arm_control[H_SHOULDER].down = h_shoulder_down;
    arm_control[H_SHOULDER].up = h_shoulder_up;
    arm_control[H_SHOULDER].off = h_shoulder_off;
    arm_control[H_SHOULDER].read_encoder = h_shoulder_read_angle;
    arm_control[H_SHOULDER].off(LEFT);
    arm_control[H_SHOULDER].off(RIGHT);

    uint32_t check_valid_angle;

    memcpy(&check_valid_angle, (uint32_t *)RIGHT_DOWN_H_SHOULDER_ADDRESS, sizeof(float));

    if(check_valid_angle == 0xFFFFFFFF)
    {
        arm_calibration_start();
    }
}

void arm_calibration_start(void)
{
    float d_angle = 0;
    float angle = 0;
    uint8_t address = 0;

    flash_erase_sector(CALIBRATION_DATA_SECTOR_NUMBER);
    chThdSleepMilliseconds(2000);


    // 3 joint on the one hand
    for(size_t part_arm = 0; part_arm < DEGREE_OF_FREEDOM_QTY; part_arm++)
    {
        // 2 side (right and left)
        for(size_t side = 0; side < ARM_QTY; side++)
        {
            address++;
            angle = arm_control[part_arm].read_encoder(side);
            arm_control[part_arm].up(side, 10000);
            chThdSleepMilliseconds(1000);
            while(1)
            {
                d_angle = arm_control[part_arm].read_encoder(side) - angle;
                if(d_angle == 0.0f)
                {
                    if(angle > 0)
                    {
                        flash_write_block(calibration_address[address-1], (uint8_t*)&angle, 4);
                    }

                    arm_control[part_arm].off(side);
                    break;
                }
                angle = arm_control[part_arm].read_encoder(side);
                chThdSleepMilliseconds(1000);
            }
            address++;
            angle = arm_control[part_arm].read_encoder(side);
            arm_control[part_arm].down(side, 10000);
            chThdSleepMilliseconds(1000);
            while(1)
            {
                d_angle = arm_control[part_arm].read_encoder(side) - angle;
                if(d_angle == 0.0f)
                {
                    if(angle > 0)
                    {
                        flash_write_block(calibration_address[address-1], (uint8_t*)&angle, 4);
                    }
                    arm_control[part_arm].off(side);
                    break;
                }
                angle = arm_control[part_arm].read_encoder(side);
                chThdSleepMilliseconds(1000);
            }
        }

    }
}


void arm_calibration_get_calibration_angle_values(uint8_t* data, size_t len)
{
    if(len < CALIBRATION_ANGLE_QTY*sizeof(float))
    {
        data = NULL;
        len = 0;
        return;
    }

    memcpy(data, (uint32_t*)BASE_CALIBRATION_ADDRESS, CALIBRATION_ANGLE_QTY*sizeof(float));
}


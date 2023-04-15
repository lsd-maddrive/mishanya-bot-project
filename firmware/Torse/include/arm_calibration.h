#ifndef TORSE_ARM_CALIBRATION_H
#define TORSE_ARM_CALIBRATION_H

#include "elbow_driver.h"
#include "vertical_shoulder_driver.h"
#include "horizontal_shoulder_driver.h"
#include "common.h"
#include "flash_f7.h"

// float size
#define ANGLE_SIZE 0x04

#define CALIBRATION_DATA_SECTOR_NUMBER 11U

#define CALIBRATION_ANGLE_QTY           12U

#define BASE_CALIBRATION_ADDRESS 0x081C0000

#define LEFT_UP_ELBOW_ADDRESS                  BASE_CALIBRATION_ADDRESS
#define LEFT_DOWN_ELBOW_ADDRESS                (LEFT_UP_ELBOW_ADDRESS + ANGLE_SIZE)
#define RIGHT_UP_ELBOW_ADDRESS                 (LEFT_DOWN_ELBOW_ADDRESS + ANGLE_SIZE)
#define RIGHT_DOWN_ELBOW_ADDRESS               (RIGHT_UP_ELBOW_ADDRESS + ANGLE_SIZE)

#define LEFT_UP_V_SHOULDER_ADDRESS             (RIGHT_DOWN_ELBOW_ADDRESS + ANGLE_SIZE)
#define LEFT_DOWN_V_SHOULDER_ADDRESS           (LEFT_UP_V_SHOULDER_ADDRESS + ANGLE_SIZE)
#define RIGHT_UP_V_SHOULDER_ADDRESS            (LEFT_DOWN_V_SHOULDER_ADDRESS + ANGLE_SIZE)
#define RIGHT_DOWN_V_SHOULDER_ADDRESS          (RIGHT_UP_V_SHOULDER_ADDRESS + ANGLE_SIZE)

#define LEFT_UP_H_SHOULDER_ADDRESS             (RIGHT_DOWN_V_SHOULDER_ADDRESS + ANGLE_SIZE)
#define LEFT_DOWN_H_SHOULDER_ADDRESS           (LEFT_UP_H_SHOULDER_ADDRESS + ANGLE_SIZE)
#define RIGHT_UP_H_SHOULDER_ADDRESS            (LEFT_DOWN_H_SHOULDER_ADDRESS + ANGLE_SIZE)
#define RIGHT_DOWN_H_SHOULDER_ADDRESS          (RIGHT_UP_H_SHOULDER_ADDRESS + ANGLE_SIZE)

void arm_calibration_start(void);
void calibration_init(void);
void arm_calibration_get_calibration_angle_values(uint8_t* data, size_t len);

#endif //TORSE_ARM_CALIBRATION_H

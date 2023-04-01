#ifndef BASE_LLD_GYROSCOPE_H
#define BASE_LLD_GYROSCOPE_H

#include "common.h"
#include "cnfg_peripherals.h"
#include "i2c.h"

typedef enum  {X = 0, Y, Z}GyroAxis;

void gyroscopeInit(uint8_t priority);

msg_t gyroscopeRead(float* rawValues);

float getAngleGyro(GyroAxis axis);

float getAngularSpeedGyro(GyroAxis axis);

#endif //BASE_LLD_GYROSCOPE_H

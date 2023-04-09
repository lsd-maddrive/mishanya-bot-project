#ifndef BASE_LLD_GYROSCOPE_H
#define BASE_LLD_GYROSCOPE_H

#include "common.h"
#include "cnfg_peripherals.h"
#include "i2c.h"

typedef enum  {X = 0, Y, Z}GyroAxis;

/**
 * @brief start i2c and setting the gyroscope operation mode,  create thread
 * @arg   priority thread
 */
void gyroscopeInit(uint8_t priority);

/**
 * @brief  reading raw values from is gyroscope
 * @arg    buffer for writing values, size - 3
 * @return status i2c
 */
msg_t gyroscopeRead(int16_t* rawValues);

/**
 * @brief  getting the angle of rotation
 * @arg    axis (x, y, z)
 * @return angle of rotation
 */
float getAngleGyro(GyroAxis axis);

/**
 * @brief  getting the angular speed
 * @arg    axis (x, y, z)
 * @return angular speed
 */
float getAngularSpeedGyro(GyroAxis axis);

/**
 * @brief  calculates the drift of values from the gyroscope
 * @arg    buffer with size 3
 * @return status i2c
 */
msg_t calculateDreifGyro(float* gyroRawData);

/**
* @brief   reading angular speed
 * @arg    buffer with size 3
 * @return status i2c
 */
msg_t readGyroSpeed(float *axisSpeed);

#endif //BASE_LLD_GYROSCOPE_H

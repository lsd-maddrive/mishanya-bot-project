#ifndef BASE_CLOSED_SYSTEM_DRIVE_H
#define BASE_CLOSED_SYSTEM_DRIVE_H

#include "common.h"
#include "odometry_base.h"
#include "motor.h"
#include "serial.h"
#include "encoder_base.h"

typedef float regulatorCoefficient;
typedef float regulatorValue;

/**
* @brief       structure for coefficient PI regulator
* @identifier1 coefficient of the P component
* @identifier2 coefficient of the I component
* @identifier3 saturation value of the integrator
* @identifier4 dead zone value of the P component
*/
typedef struct{
    regulatorCoefficient kp;
    regulatorCoefficient ki;
    regulatorCoefficient integSaturation;
    regulatorCoefficient pDeadZone;
}PIregulator;

/**
* @brief       structure for regulator speed wheels
* @identifier1 reference speed
* @identifier2 real speed
* @identifier3 value of error
* @identifier4 value of integrator
* @identifier5 output regulator
*/
typedef struct{
    regulatorValue   refSpeed;
    regulatorValue   realSpeed;
    regulatorValue   pErrSpeed;
    regulatorValue   intgSpeed;
    regulatorValue   speedControlValue;
}RegulatorValueMotor;

/**
* @brief Initialization odometry and motors, create thread
* @args priority
*/
void driveCSInit(uint8_t prio);

/**
* @brief Speed setting
* @args speed and units
*/
void setRefSpeed(type_motor motor_n, float speed, SpeedUnits units);

/**
* @brief Reset the values of  PI regulator
*/
void ResetSpeedRegulator(void);

#endif //BASE_CLOSED_SYSTEM_DRIVE_H

#ifndef BASE_KINEMATICS_H
#define BASE_KINEMATICS_H

#include "common.h"
#include "lld_gyroscope.h"
#include "closed_system_drive.h"

typedef enum {WHEEL_1, WHEEL_2, WHEEL_3} WheelNumber;

/**
* @brief calculation and setting of the angular speed of the wheels
*/
void  setBaseSpeed(float vxGlobal, float vyGlobal, float angularSpeed);

/**
* @brief Initialization gyroscope and thread closed system
*/
void  initKinematics(void);

/**
* @brief Get angular speed
* @note units revolutions per second
* @args number of wheel
* @return distance
*/
float getAngularSpeedWheel(WheelNumber wheelNumber);

#endif

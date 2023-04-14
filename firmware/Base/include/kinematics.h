#ifndef BASE_KINEMATICS_H
#define BASE_KINEMATICS_H

#include "common.h"
#include "lld_gyroscope.h"
#include "closed_system_drive.h"

typedef enum {WHEEL_1, WHEEL_2, WHEEL_3} WheelNumber;

void  calculationSpeedWheelsRobots(float vxGlobal, float vyGlobal, float angularSpeed);
void  initKinematics(void);
float getAngularSpeedWheel(WheelNumber wheelNumber);

#endif
#include "kinematics.h"

float angularSpeedWheel1 = 0;
float angularSpeedWheel2 = 0;
float angularSpeedWheel3 = 0;

void setBaseSpeed(float vxGlobal, float vyGlobal, float angularSpeed) {
    float realAngleZ   = getAngleGyro(Z);
    angularSpeedWheel1 = (1/R) * ((-1) * vxGlobal * cosf(realAngleZ * GRAD_TO_RAD)
                         - vyGlobal * sinf(realAngleZ * GRAD_TO_RAD) + L * angularSpeed);
    angularSpeedWheel2 = (1/R) * (vxGlobal * cosf(realAngleZ * GRAD_TO_RAD - THETA)
                         + vyGlobal * sinf(realAngleZ * GRAD_TO_RAD - THETA) + L * angularSpeed);
    angularSpeedWheel3 = (1/R) * (vxGlobal * cosf(realAngleZ * GRAD_TO_RAD + THETA)
                         + vyGlobal * sinf(realAngleZ * GRAD_TO_RAD + THETA) + L * angularSpeed);

    setRefSpeed(MOTOR_1, RAD_TO_REVS  *  angularSpeedWheel1, REVS_PER_SEC);
    setRefSpeed(MOTOR_2, RAD_TO_REVS  *  angularSpeedWheel2, REVS_PER_SEC);
    setRefSpeed(MOTOR_3, RAD_TO_REVS  *  angularSpeedWheel3, REVS_PER_SEC);
}

void initKinematics(void) {
    driveCSInit(1);
    gyroscopeInit(1);
    ResetSpeedRegulatorWheel1();
    ResetSpeedRegulatorWheel2();
    ResetSpeedRegulatorWheel3();
}

float getAngularSpeedWheel(WheelNumber wheelNumber) {
    if (wheelNumber == WHEEL_1)
        return angularSpeedWheel1 * RAD_TO_REVS;
    else if (wheelNumber == WHEEL_2)
        return angularSpeedWheel2 * RAD_TO_REVS;
    else if (wheelNumber == WHEEL_3)
        return angularSpeedWheel3 * RAD_TO_REVS;
    else
        return -1;
}

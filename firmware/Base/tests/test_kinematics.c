#include "test.h"
#include "kinematics.h"
#include "serial.h"
#include "lld_gyroscope.h"
#include "odometry_base.h"

static const SerialConfig sdcfg = {
        .speed  = 115200,
        .cr1    = 0,
        .cr2    = 0,
        .cr3    = 0
};

void testKinematicsBase(void) {
    char  sym           = 0;
    float vX            = 0;
    float vY            = 0;
    float angularSpeed  = 0;
    float speedWheel1   = 0;
    float speedWheel2   = 0;
    float speedWheel3   = 0;
    float realSpeed1    = 0;
    float realSpeed2    = 0;
    float realSpeed3    = 0;

    float angle         = 0;

    bool  StartTransfer = false;
    debug_stream_init();
    initKinematics();
    sdStart(&SD4, &sdcfg);
    palSetPadMode(GPIOD, 0, PAL_MODE_ALTERNATE(8));
    palSetPadMode(GPIOD, 1, PAL_MODE_ALTERNATE(8));

    systime_t time = chVTGetSystemTime();
    while (1) {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        if (sym == 's')
        {
            StartTransfer = TRUE;
            vX            = 0;
            vY            = 0.3;
            angularSpeed  = 0;
        }
        switch (sym)
        {
            case ' ':
                ResetSpeedRegulatorWheel1();
                ResetSpeedRegulatorWheel2();
                ResetSpeedRegulatorWheel3();
                vX           = 0;
                vY           = 0;
                angularSpeed = 0;
                break;
            case 'q':
                vX            = 0;
                vY            = 0;
                angularSpeed  = 1.5;
                break;
            case 'e':
                vX            = -0.6;
                vY            = -0.2;
                angularSpeed  =  1;
                break;
            default: {}
        }
        setBaseSpeed(vX, vY, angularSpeed);
        speedWheel1 = getAngularSpeedWheel(WHEEL_1);
        speedWheel2 = getAngularSpeedWheel(WHEEL_2);
        speedWheel3 = getAngularSpeedWheel(WHEEL_3);
        realSpeed1  = odometryGetWheelSpeed(REVS_PER_SEC, ENCODER_1);
        realSpeed2  = odometryGetWheelSpeed(REVS_PER_SEC, ENCODER_2);
        realSpeed3  = odometryGetWheelSpeed(REVS_PER_SEC, ENCODER_3);
        angle       = getAngleGyro(Z);
        if (StartTransfer)
        {
            sdWrite(&SD4, (uint8_t*)&speedWheel1, 4);
            sdWrite(&SD4, (uint8_t*)&speedWheel2, 4);
            sdWrite(&SD4, (uint8_t*)&speedWheel3, 4);
            sdWrite(&SD4, (uint8_t*)&realSpeed1,  4);
            sdWrite(&SD4, (uint8_t*)&realSpeed2,  4);
            sdWrite(&SD4, (uint8_t*)&realSpeed3,  4);

            time = chThdSleepUntilWindowed(time, TIME_MS2I(10) + time);
        }
    }
}

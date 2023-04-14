#include "test.h"
#include "kinematics.h"
#include "serial.h"
#include "odometry_base.h"

static const SerialConfig sdcfg = {
        .speed  = 115200,
        .cr1    = 0,
        .cr2    = 0,
        .cr3    = 0
};

void testKinematicsBase(void) {
    char  sym           = 0;
    float vX            = 0.5;
    float vY            = 0.7;
    float angularSpeed  = 0;
    float speedWheel1   = 0;
    float speedWheel2   = 0;
    float speedWheel3   = 0;
    float realSpeed1    = 0;

    bool  StartTransfer = false;
    debug_stream_init();
    initKinematics();
    sdStart(&SD4, &sdcfg);
    palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOB, 9, PAL_MODE_ALTERNATE(7));

    systime_t time = chVTGetSystemTime();
    while (1) {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        if (sym == 's')
        {
            StartTransfer = TRUE;
        }
        switch (sym)
        {
            case ' ':
                ResetSpeedRegulator();
                vX           = 0;
                vY           = 0;
                angularSpeed = 0;
                break;
            case 'q':
                vX            = 0;
                vY            = 0;
                angularSpeed  = 10;
                break;
            case 'e':
                vX            = -0.6;
                vY            = -0.2;
                angularSpeed  = 0.5;
                break;
            default: {}
        }
        calculationSpeedWheelsRobots(vX, vY, angularSpeed);
        speedWheel1 = getAngularSpeedWheel(WHEEL_1);
        speedWheel2 = getAngularSpeedWheel(WHEEL_2);
        speedWheel3 = getAngularSpeedWheel(WHEEL_3);
        realSpeed1  = odometryGetWheelSpeed(REVS_PER_SEC, ENCODER_1);

        if (StartTransfer)
        {
            sdWrite(&SD4, (uint8_t*)&speedWheel1, 4);
            sdWrite(&SD4, (uint8_t*)&realSpeed1, 4);
            time = chThdSleepUntilWindowed(time, TIME_MS2I(25)+time);
        }
//        else
//        {
//            dbgprintf("w1:%d w2:%d w3:%d\n\r",(int)(speedWheel1 * 1000),
//            (int)(speedWheel2 * 1000), (int)(speedWheel3 * 1000));
//            time = chThdSleepUntilWindowed(time, TIME_MS2I(100)+time);
//        }

    }
}
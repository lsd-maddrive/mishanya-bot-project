#include "test.h"
#include "lld_gyroscope.h"
#include "serial.h"

bool StartTransfer = FALSE;
typedef struct {
    float  X;
    float  Y;
    float  Z;
}AngularSpeed;

typedef struct {
    float  X;
    float  Y;
    float  Z;
}Angle;

void testGyroscope(void) {
    AngularSpeed angularSpeed;
    Angle        angle;

    gyroscopeInit(1);
    debug_stream_init();


    systime_t time = chVTGetSystemTime();
    while(1) {
        angularSpeed.X = getAngularSpeedGyro(X);
        angularSpeed.Y = getAngularSpeedGyro(Y);
        angularSpeed.Z = getAngularSpeedGyro(Z);

        angle.X        = getAngleGyro(X);
        angle.Y        = getAngleGyro(Y);
        angle.Z        = getAngleGyro(Z);

        char start_sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        if(start_sym == 'g'){
            StartTransfer = TRUE;
        }
        else if(start_sym == 't'){
            StartTransfer = FALSE;
        }
        if(StartTransfer)
        {
            sdWrite(&SD3, (uint8_t*)&angle.Z, 4);
        }
        time = chThdSleepUntilWindowed(time, TIME_MS2I(10) + time);

    }
}
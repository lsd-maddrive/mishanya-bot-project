#include "test.h"
#include "lld_gyroscope.h"
#include "serial.h"

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

//        dbgprintf("speed X:%d speed Y:%d speed Z:%d\n\r", (int)angularSpeed.X,
//                  (int)angularSpeed.Y, (int)angularSpeed.Z);
//
//        dbgprintf("angle  X:%d angle Y:%d angle Z:%d\n\r", (int)angle.X ,
//                  (int)angle.Y , (int)angle.Z );
        time = chThdSleepUntilWindowed(time, TIME_MS2I(100)+time);

    }
}
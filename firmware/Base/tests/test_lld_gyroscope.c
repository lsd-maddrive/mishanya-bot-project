#include "test.h"
#include "lld_gyroscope.h"
#include "serial.h"
#include "closed_system_drive.h"

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

static const SerialConfig sdcfg = {
        .speed  = 115200,
        .cr1    = 0,
        .cr2    = 0,
        .cr3    = 0
};

void testGyroscope(void) {
    AngularSpeed angularSpeed;
    Angle        angle;
    char         sym           = 0;
    float        speedInput    = 0;

    gyroscopeInit(1);
    driveCSInit(1);
    debug_stream_init();
    sdStart(&SD4, &sdcfg);
    palSetPadMode(GPIOD, 0, PAL_MODE_ALTERNATE(8) );
    palSetPadMode(GPIOD, 1, PAL_MODE_ALTERNATE(8) );


    systime_t time = chVTGetSystemTime();
    while (1) {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        if (sym == 's'){
            StartTransfer = TRUE;
            speedInput = 0.9;
        }
        switch (sym) {
            case ' ':
                speedInput = 0;
                ResetSpeedRegulatorWheel1();
                ResetSpeedRegulatorWheel2();
                ResetSpeedRegulatorWheel3();
                break;
            case 'q':
                speedInput = 0;
                break;
            case 'e':
                speedInput = -0.4;
                break;
            default: {}
        }
        setRefSpeed(MOTOR_1,speedInput, REVS_PER_SEC);
        setRefSpeed(MOTOR_2,speedInput, REVS_PER_SEC);
        setRefSpeed(MOTOR_3,speedInput, REVS_PER_SEC);
        angularSpeed.X = getAngularSpeedGyro(X);
        angularSpeed.Y = getAngularSpeedGyro(Y);
        angularSpeed.Z = getAngularSpeedGyro(Z);

        angle.X        = getAngleGyro(X);
        angle.Y        = getAngleGyro(Y);
        angle.Z        = getAngleGyro(Z);

        char start_sym = sdGetTimeout(&SD4, TIME_IMMEDIATE);
        if (start_sym == 'g')
        {
            StartTransfer = TRUE;
        }
        else if (start_sym == 't')
        {
            StartTransfer = FALSE;
        }
        if (StartTransfer)
        {
            sdWrite(&SD4, (uint8_t*)&angle.Z, 4);
        }
        time = chThdSleepUntilWindowed(time, TIME_MS2I(10) + time);
    }
}

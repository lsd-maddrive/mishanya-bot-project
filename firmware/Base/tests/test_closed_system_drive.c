#include "test.h"
#include "serial.h"
#include "closed_system_drive.h"

#define MATLAB_PI_REGULATOR

#ifdef MATLAB_PI_REGULATOR
static const SerialConfig sdcfg = {
    .speed  = 115200,
    .cr1    = 0,
    .cr2    = 0,
    .cr3    = 0
};
#endif

void testPISpeedMotor(void) {
    float speedInput1   = 0;
    float speedInput2   = 0;
    float speedInput3   = 0;
    float speedOutput   = 0;
    bool  StartTransfer = FALSE;
    char  sym           = 0;

    driveCSInit(1);
    debug_stream_init();
    ResetSpeedRegulatorWheel1();
    ResetSpeedRegulatorWheel2();
    ResetSpeedRegulatorWheel3();
    #ifdef MATLAB_PI_REGULATOR
        sdStart(&SD4, &sdcfg);
        palSetPadMode(GPIOD, 0, PAL_MODE_ALTERNATE(8));
        palSetPadMode(GPIOD, 1, PAL_MODE_ALTERNATE(8));
    #endif
    systime_t time = chVTGetSystemTime();
    while (1)
    {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
            if (sym == 's')
            {
                StartTransfer = TRUE;
                speedInput1   = 0.9;
                speedInput2   = 0;
                speedInput3   = 0.9;

            }
        switch (sym)
        {
            case ' ':
                speedInput1 = 0;
                speedInput2 = 0;
                speedInput3 = 0;
                ResetSpeedRegulatorWheel1();
                ResetSpeedRegulatorWheel2();
                ResetSpeedRegulatorWheel3();
                break;
            case 'q':
                speedInput1   = 0;
                speedInput2   = 0;
                speedInput3   = 0;
                break;
            case 'e':
                speedInput1   = 0.6;
                speedInput2   = 0.6;
                speedInput3   = 0.6;
                break;
            default: {}
        }

        setRefSpeed(MOTOR_1,speedInput1, REVS_PER_SEC);
        setRefSpeed(MOTOR_2,speedInput2, REVS_PER_SEC);
        setRefSpeed(MOTOR_3,speedInput3, REVS_PER_SEC);
        speedOutput = odometryGetWheelSpeed(REVS_PER_SEC, ENCODER_3);

#ifdef MATLAB_PI_REGULATOR
        if (StartTransfer)
        {
            sdWrite(&SD4, (uint8_t*)&speedOutput, 4);
        }
        time = chThdSleepUntilWindowed(time, TIME_MS2I(25)+time);
#else
        //dbgprintf("In:%d Out:%d\n\r",(int)(speed_input*100),
        //(int)(speed_output));
        time = chThdSleepUntilWindowed(time, MS2ST(100)+time);
#endif
    }
}


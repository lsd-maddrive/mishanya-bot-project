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
    float speedInput    = 0;
    float speedOutput   = 0;
    bool  StartTransfer = FALSE;
    char  sym           = 0;

    driveCSInit(1);
    debug_stream_init();
    ResetSpeedRegulator();
    #ifdef MATLAB_PI_REGULATOR
        sdStart(&SD4, &sdcfg);
        palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(7));
        palSetPadMode(GPIOB, 9, PAL_MODE_ALTERNATE(7));
    #endif
    systime_t time = chVTGetSystemTime();
    while (1)
    {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
            if (sym == 's')
            {
                StartTransfer = TRUE;
                speedInput = 0.6;
            }
        switch (sym)
        {
            case ' ':
                speedInput = 0;
                ResetSpeedRegulator();
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


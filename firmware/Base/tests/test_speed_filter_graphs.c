#include "test.h"
#include "common.h"
#include "motor.h"
#include "odometry_base.h"
#include "serial.h"

#define MATLAB_ODOMETRY

#ifdef MATLAB_ODOMETRY
static const SerialConfig sdcfg = {
    .speed  = 115200,
    .cr1    = 0,
    .cr2    = 0,
    .cr3    = 0
};
#endif

void test_speed_filter_graphs(void)
{
    int8_t flag_percent = 1;
    float delta_per     = 10;
    float duty_cycle    = 0;
    float speed_1       = 0;
    float speed_2       = 0;
    float speed_3       = 0;
    float spdRaw        = 0;
    bool StartTransfer = FALSE;
    debug_stream_init();
    odometryInit();
    lldMotorInit(MOTOR_1);
    lldMotorInit(MOTOR_2);
    lldMotorInit(MOTOR_3);
    #ifdef MATLAB_ODOMETRY
<<<<<<< HEAD
        sdStart(&SD4, &sdcfg);
        palSetPadMode(GPIOD, 0, PAL_MODE_ALTERNATE(8));
        palSetPadMode(GPIOD, 1, PAL_MODE_ALTERNATE(8));
=======
        sdStart(&SD5, &sdcfg);
        palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(7));
        palSetPadMode(GPIOB, 9, PAL_MODE_ALTERNATE(7));
>>>>>>> develop
    #endif
    systime_t time = chVTGetSystemTime();
    while (1)
    {
        char sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        switch (sym)
        {
            case ' ':
                duty_cycle = 0;
                odometryReset(ENCODER_1);
                odometryReset(ENCODER_2);
                odometryReset(ENCODER_3);
                break;
            case 'w':
                duty_cycle += delta_per;
                break;
            case 's':
                duty_cycle -= delta_per;
                break;
            default: {}
        }
        duty_cycle = CLIP_VALUE(duty_cycle, -100, 100);
        lldSetMotorPower(MOTOR_1, duty_cycle, flag_percent);
        lldSetMotorPower(MOTOR_2, duty_cycle, flag_percent);
        lldSetMotorPower(MOTOR_3, duty_cycle, flag_percent);
        speed_1 = odometryGetWheelSpeed(CM_S, ENCODER_1);
        spdRaw  = getRaw(CM_S, ENCODER_1);
        speed_2 = odometryGetWheelSpeed(CM_S, ENCODER_2);
        speed_3 = odometryGetWheelSpeed(CM_S, ENCODER_3);
<<<<<<< HEAD
=======

>>>>>>> develop
        #ifdef MATLAB_ODOMETRY
            char start_sym = sdGetTimeout(&SD4, TIME_IMMEDIATE);
            time = chThdSleepUntilWindowed(time, TIME_MS2I(40) + time);
<<<<<<< HEAD
            if (start_sym == 'g'){
                StartTransfer = TRUE;
            }
            else if (start_sym == 't'){
=======
            if (start_sym == 'g')
            {
                StartTransfer = TRUE;
            }
            else if (start_sym == 't')
            {
>>>>>>> develop
                StartTransfer = FALSE;
            }
            if (StartTransfer)
            {
                //sdWrite(&SD5, (uint8_t*)&speed_1, 4);
                //sdWrite(&SD5, (uint8_t*)&speed_2, 4);
               sdWrite(&SD4, (uint8_t*)&speed_3, 4);
                //sdWrite(&SD5, (uint8_t*)&spdRaw,  4);
            }
            //time = chThdSleepUntilWindowed (time, TIME_MS2I(10) + time);
        #else
            dbgprintf("Wheel1: Speed1:%d ",
//                      "Wheel2: Speed2:%d"
//                      "Wheel3: Speed3:%d\n\r",
                      (int)(speed_1));
//                      (int)(speed_2),
//                      (int)(speed_3));
            time = chThdSleepUntilWindowed(time, TIME_MS2I(100) + time);
        #endif
    }
}

#include "test.h"
#include "odometry_base.h"
#include "serial.h"
#include "encoder_base.h"

void testOdometryBase(type_encoder encoder)
{
    float dist = 0;
    float speed = 0;
    odometryInit();
    debug_stream_init();
    systime_t time = chVTGetSystemTime();
    while (1)
    {
        char sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        if (sym == ' ')
        {
            odometryReset(encoder);
        }
        dist    = odometryGetWheelDistance(CM, encoder);
        speed   = odometryGetWheelSpeed(CM_S, encoder);
        dbgprintf("Distance:%d Speed:%d \n\r", (int)dist, (int)(speed));
        time = chThdSleepUntilWindowed(time, TIME_MS2I(100)+time);
    }
}

void testOdometryBaseAll(void)
{
    float dist_1 = 0;
    float speed_1 = 0;
    float dist_2 = 0;
    float speed_2 = 0;
    float dist_3 = 0;
    float speed_3 = 0;
    debug_stream_init();
    odometryInit();
    systime_t time = chVTGetSystemTime();
    while (1)
    {
        char sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        if (sym == ' ')
        {
            odometryReset(ENCODER_1);
            odometryReset(ENCODER_2);
            odometryReset(ENCODER_3);
        }
        dist_1  = odometryGetWheelDistance(CM, ENCODER_1);
        speed_1 = odometryGetWheelSpeed(CM_S, ENCODER_1);
        dist_2  = odometryGetWheelDistance(CM, ENCODER_2);
        speed_2 = odometryGetWheelSpeed(CM_S, ENCODER_2);
        dist_3  = odometryGetWheelDistance(CM, ENCODER_3);
        speed_3 = odometryGetWheelSpeed(CM_S, ENCODER_3);
        dbgprintf("Wheel1: Dist1:%d Speed1:%d "
                  "Wheel2: Dist2:%d Speed2:%d "
                  "Wheel3: Dist3:%d Speed3:%d\n\r",
                  (int)(dist_1), (int)(speed_1),
                  (int)(dist_2), (int)(speed_2),
                  (int)(dist_3), (int)speed_3);
        time = chThdSleepUntilWindowed(time, TIME_MS2I(100) + time);
    }
}


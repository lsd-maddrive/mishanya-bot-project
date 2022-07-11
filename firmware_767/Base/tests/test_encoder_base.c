#include <test.h>
#include <encoder_base.h>
#include <serial.h>
#include <common.h>

void test_encoder_base(void)
{
    int16_t tic = 0;
    bool dr = 0;
    float revs = 0;
    char sym = 0;
    GetTypeEncoder(ENCODER_2);
    lldEncoderInit();
    debug_stream_init();
    systime_t time = chVTGetSystemTime();

    while(1)
    {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        if(sym == ' ')
        {
            ResetEncoder();
        }
        else
        {
            tic = GetEncoderRawTicks();
            dr = GetEncoderDirection();
            revs = 1000*GetEncoderRawRevs();
        }
        dbgprintf("Tic count:%d Rev count:%d Direction:%d\n\r",tic,
                              (int)revs,dr);
        time = chThdSleepUntilWindowed(time, TIME_MS2I(100)+time);
    }
}


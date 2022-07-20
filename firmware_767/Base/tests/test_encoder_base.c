#include <test.h>
#include <encoder_base.h>
#include <serial.h>
#include <common.h>

void test_encoder_base(type_encoder encoder)
{
    int16_t tic = 0;
    bool dr = 0;
    float revs = 0;
    char sym = 0;
    lldEncoderInit(encoder);
    debug_stream_init();
    systime_t time = chVTGetSystemTime();

    while(1)
    {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        if(sym == ' ')
        {
            ResetEncoder(encoder);
        }
        else
        {
            tic = GetEncoderRawTicks(encoder);
            dr = GetEncoderDirection(encoder);
            revs = 1000*GetEncoderRawRevs(encoder);
        }
        dbgprintf("ENC: Tic:%d Rev:%d Direct:%d\n\r",
                  tic, (int)revs, dr);

        time = chThdSleepUntilWindowed(time, TIME_MS2I(300)+time);
    }
}


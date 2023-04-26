#include <test.h>
#include <encoder_base.h>
#include <serial.h>
#include <common.h>

static const SerialConfig sdcfg = {
        .speed  = 115200,
        .cr1    = 0,
        .cr2    = 0,
        .cr3    = 0
};

void test_encoder_base_all(void)
{
    bool StartTransfer = false;
    int16_t tic_1 = 0;
    bool dr_1 = 0;
    float revs_1 = 0;
    int16_t tic_2 = 0;
    bool dr_2 = 0;
    float revs_2 = 0;
    int16_t tic_3 = 0;
    bool dr_3 = 0;
    float revs_3 = 0;
    float duty_cycle = 0;
    float delta_percent  = 10;
    char sym = 0;
    lldEncoderInit(ENCODER_1);
    lldEncoderInit(ENCODER_2);
    lldEncoderInit(ENCODER_3);
    lldMotorInit(MOTOR_3);
    debug_stream_init();
    sdStart(&SD4, &sdcfg);
    palSetPadMode(GPIOD, 0, PAL_MODE_ALTERNATE(8));
    palSetPadMode(GPIOD, 1, PAL_MODE_ALTERNATE(8));
    systime_t time = chVTGetSystemTime();
    while (1)
    {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        switch(sym) {
            case ' ':
                duty_cycle = 0;
                ResetEncoder(ENCODER_1);
                ResetEncoder(ENCODER_2);
                ResetEncoder(ENCODER_3);
                break;
            case 'w':
                duty_cycle += delta_percent;
                break;
            case 's':
                duty_cycle -= delta_percent;
                break;
            default: {}
        }
        duty_cycle = CLIP_VALUE(duty_cycle, -100, 100);
        lldSetMotorPower(MOTOR_3, duty_cycle, 1);
        tic_1 = GetEncoderRawTicks(ENCODER_3);
        dr_1 = GetEncoderDirection(ENCODER_3);
        revs_1 = GetEncoderRawRevs(ENCODER_3);
        tic_2 = GetEncoderRawTicks(ENCODER_2);
        dr_2 = GetEncoderDirection(ENCODER_2);
        revs_2 = 1000*GetEncoderRawRevs(ENCODER_2);
        tic_3 = GetEncoderRawTicks(ENCODER_3);
        dr_3 = GetEncoderDirection(ENCODER_3);
        revs_3 = 1000*GetEncoderRawRevs(ENCODER_3);
        char start_sym = sdGetTimeout(&SD4, TIME_IMMEDIATE);
        time = chThdSleepUntilWindowed(time, TIME_MS2I(10) + time);
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
            sdWrite(&SD4, (uint8_t*)&tic_1, 4);
            sdWrite(&SD4, (uint8_t*)&dr_1, 4);
            sdWrite(&SD4, (uint8_t*)&revs_1, 4);
        }
//        dbgprintf("ENC1: Tic1:%d Rev1:%d Direct1:%d "
//                  "ENC2: Tic2:%d Rev2:%d Direct2:%d "
//                  "ENC3: Tic3:%d Rev3:%d Direct3:%d\n\r",
//                  tic_1, (int)revs_1, dr_1, tic_2, (int)revs_2, dr_2,
//                  tic_3, (int)revs_3, dr_3);

//       time = chThdSleepUntilWindowed(time, TIME_MS2I(300)+time);
    }
}


void test_encoder_base(type_encoder encoder)
{
    int16_t tic = 0;
    bool dr = 0;
    float revs = 0;
    char sym = 0;
    lldEncoderInit(encoder);
    debug_stream_init();
    systime_t time = chVTGetSystemTime();

    while (1)
    {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        if (sym == ' ')
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

        time = chThdSleepUntilWindowed(time, TIME_MS2I(300) + time);
    }
}


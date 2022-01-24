#include <test.h>
#include <lld_control_servo.h>
#include <serial.h>
#include <common.h>

void test_lld_servo(int8_t servo)
{
    int16_t delta = 100;
    int16_t duty_cycle = 0;
    lld_control_servo_init();
    debug_stream_init();
    systime_t time = chVTGetSystemTime();

    while(1)
    {
        char sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        switch(sym)
        {
            case 'a':
                duty_cycle += delta;
                break;
            case 'd':
                 duty_cycle -= delta;
                 break;
            default: ;
        }
        setServoPtr(duty_cycle, servo);
        dbgprintf("duty_cycle:%d\n\r",(int)duty_cycle);
        time = chThdSleepUntilWindowed (time, TIME_MS2I(100)+time);

    }

}

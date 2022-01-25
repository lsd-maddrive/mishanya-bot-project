#include <test.h>
#include <lld_control_servo.h>
#include <serial.h>
#include <common.h>

void test_lld_servo(type_servo servo)
{
    int16_t delta = 100;
    int16_t duty_cycle = 0;
    int16_t high = 0;
    int16_t low = 0;
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

        high = get_servo_high_limit(servo);
        low = get_servo_low_limit(servo);
        duty_cycle = CLIP_VALUE(duty_cycle,low,high);
        lld_set_dutycycle_servo(duty_cycle, servo);
        dbgprintf("duty_cycle:%d\n\r",(int)duty_cycle);
        time = chThdSleepUntilWindowed (time, TIME_MS2I(100)+time);

    }

}

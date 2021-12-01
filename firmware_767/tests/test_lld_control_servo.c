#include <test.h>
#include <lld_control_servo.h>
#include <serial.h>

void test_lld_servo_left_hand(servo_arm *servo)
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
        duty_cycle = CLIP_VALUE(duty_cycle,servo->left_hand_limit,
                                servo->right_hand_limit);
        lld_control_servo_hand(duty_cycle, servo);
        dbgprintf("Angle:%d\n\r",(int)duty_cycle);
        time = chThdSleepUntilWindowed (time, TIME_MS2I(100)+time);

    }

}

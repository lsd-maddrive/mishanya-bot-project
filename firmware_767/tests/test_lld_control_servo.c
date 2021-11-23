#include <test.h>
#include <lld_control_servo.h>
#include <serial.h>

void test_lld_servo_left_hand(void)
{
    int16_t delta = 100;
    int16_t duty_cycle = 0;
    lld_control_servo_init(left_hand.line);
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
        duty_cycle = CLIP_VALUE(duty_cycle,left_hand.left_hand_limit,
                                left_hand.right_hand_limit);
        lld_control_servo_hand(duty_cycle,left_hand.left_hand_limit,
                               left_hand.right_hand_limit,left_hand.channel);
        dbgprintf("Angle:%d\n\r",(int)duty_cycle);
        time = chThdSleepUntilWindowed (time, TIME_MS2I(100)+time);

    }

}

void test_lld_servo_right_hand(void)
{
    int16_t delta = 100;
    int16_t duty_cycle = 0;
    lld_control_servo_init(right_hand.line);
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
        duty_cycle = CLIP_VALUE(duty_cycle,right_hand.left_hand_limit,
                                right_hand.right_hand_limit);
        lld_control_servo_hand(duty_cycle,right_hand.left_hand_limit,
                               right_hand.right_hand_limit,right_hand.channel);
        dbgprintf("Angle:%d\n\r",(int)duty_cycle);
        time = chThdSleepUntilWindowed (time, TIME_MS2I(100)+time);

    }
}

void test_lld_servo_left_wrist(void)
{
    int16_t delta = 100;
    int16_t duty_cycle = 0;
    lld_control_servo_init(left_wrist.line);
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
        duty_cycle = CLIP_VALUE(duty_cycle,left_wrist.left_hand_limit,
                                left_wrist.right_hand_limit);
        lld_control_servo_hand(duty_cycle,left_wrist.left_hand_limit,
                               left_wrist.right_hand_limit,left_wrist.channel);
        dbgprintf("Angle:%d\n\r",(int)duty_cycle);
        time = chThdSleepUntilWindowed (time, TIME_MS2I(100)+time);

    }
}

void test_lld_servo_right_wrist(void)
{
    int16_t delta = 100;
    int16_t duty_cycle = 0;
    lld_control_servo_init(right_wrist.line);
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
        duty_cycle = CLIP_VALUE(duty_cycle,right_wrist.left_hand_limit,
                                right_wrist.right_hand_limit);
        lld_control_servo_hand(duty_cycle,right_wrist.left_hand_limit,
                             right_wrist.right_hand_limit,right_wrist.channel);
        dbgprintf("Angle:%d\n\r",(int)duty_cycle);
        time = chThdSleepUntilWindowed (time, TIME_MS2I(100)+time);

    }
}

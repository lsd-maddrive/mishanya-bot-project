#include <test.h>
#include <lld_control_servo.h>
#include <serial.h>

/**
 * @brief Test for servo in hand
 * @note value raw duty cycle
 */
void test_lld_servo_hand(void)
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
        duty_cycle = Check(duty_cycle,LEFT_SERVO_HAND, RIGHT_SERVO_HAND);
        lld_control_servo_hand(duty_cycle);
        dbgprintf("Angle:%d\n\r",(int)duty_cycle);
        time = chThdSleepUntilWindowed (time, TIME_MS2I(100)+time);

    }

}

/**
 * @brief Test for servo in wrist
 * @note value raw duty cycle
 */
void test_lld_servo_wrist(void)
{
    int16_t delta = 200;
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
        duty_cycle = Check(duty_cycle,LEFT_SERVO_WRIST, RIGHT_SERVO_WRIST);
        lld_control_servo_wrist(duty_cycle);
        dbgprintf("Angle:%d\n\r",(int)duty_cycle);
        time = chThdSleepUntilWindowed (time, TIME_MS2I(100)+time);

    }
}

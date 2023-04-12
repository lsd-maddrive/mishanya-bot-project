#include "test.h"
#include "common.h"
#include "motor.h"
#include "serial.h"

void testlldMotor(type_motor motor_n)
{
    int8_t flag_percent = 0;
    float delta = 50;
    float duty_cycle = 0;
    char sym = 0;
    lldMotorInit(motor_n);
    debug_stream_init();
    systime_t time = chVTGetSystemTime();

    while (1)
    {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        switch (sym)
        {
            case ' ':
                duty_cycle = 0;
                break;
            case 'w':
                duty_cycle += delta;
                break;
            case 's':
                duty_cycle -= delta;
                break;
            default: {}
        }
        lldSetMotorPower(motor_n, duty_cycle, flag_percent);
        dbgprintf("Speed:%d \n\r", (int)duty_cycle);
        time = chThdSleepUntilWindowed(time, TIME_MS2I(100) + time);
    }
}

void testlldMotorAll(void)
{
    float delta = 50;
    int8_t flag_percent = 0;
    float duty_cycle = 0;
    char sym = 0;
    lldMotorInit(MOTOR_1);
    lldMotorInit(MOTOR_2);
    lldMotorInit(MOTOR_3);
    debug_stream_init();
    systime_t time = chVTGetSystemTime();

    while (1)
    {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        switch (sym)
        {
            case ' ':
                duty_cycle = 0;
                break;
            case 'w':
                duty_cycle += delta;
                break;
            case 's':
                duty_cycle -= delta;
                break;
            default: {}
        }
        lldSetMotorPower(MOTOR_1, duty_cycle, flag_percent);
        lldSetMotorPower(MOTOR_2, duty_cycle, flag_percent);
        lldSetMotorPower(MOTOR_3, duty_cycle, flag_percent);
        dbgprintf("Speed:%d \n\r", (int)duty_cycle);
        time = chThdSleepUntilWindowed(time, TIME_MS2I(100) + time);
    }
}

void testlldMotorPer(type_motor motor_n)
{
    int8_t flag_percent = 1;
    float delta_per = 10;
    float duty_cycle = 0;
    char sym = 0;
    lldMotorInit(motor_n);
    debug_stream_init();
    systime_t time = chVTGetSystemTime();
    while (1)
    {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        switch (sym)
        {
            case ' ':
                duty_cycle = 0;
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
        lldSetMotorPower(motor_n, duty_cycle, flag_percent);
        dbgprintf("Speed:%d \n\r", (int)duty_cycle);
        time = chThdSleepUntilWindowed(time, TIME_MS2I(100) + time);
    }
}

void testlldMotorPerAll(void)
{
    int8_t flag_percent = 1;
    float delta_per = 10;
    float duty_cycle = 0;
    char sym = 0;
    lldMotorInit(MOTOR_1);
    lldMotorInit(MOTOR_2);
    lldMotorInit(MOTOR_3);
    debug_stream_init();
    systime_t time = chVTGetSystemTime();
    while (1)
    {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        switch (sym)
        {
            case ' ':
                duty_cycle = 0;
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
        dbgprintf("Speed:%d \n\r", (int)duty_cycle);
        time = chThdSleepUntilWindowed(time, TIME_MS2I(100) + time);
    }
}

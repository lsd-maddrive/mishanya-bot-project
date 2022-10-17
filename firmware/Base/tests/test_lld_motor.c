#include "test.h"
#include "common.h"
#include "motor.h"
#include "serial.h"

void test_lld_motor(type_motor motor_n)
{
    #define delta 500;
    float duty_cycle = 0;
    char sym = 0;
    lld_motor_init(motor_n);
    debug_stream_init();
    systime_t time = chVTGetSystemTime();

    while(1)
    {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        switch(sym)
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
            default: ;
        }
        lld_motor(motor_n, duty_cycle);
        dbgprintf("Speed:%d \n\r",(int)duty_cycle);
        time = chThdSleepUntilWindowed(time, TIME_MS2I(100)+time);
    }
    }

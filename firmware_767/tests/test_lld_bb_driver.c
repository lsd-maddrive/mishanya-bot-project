#include <tests.h>
#include <lld_bb_driver.h>
#include <lld_bridge_system.h>
#include <serial.h>

void test_lld_bb(type_wheel wheel)
{
    char sym=0;
    int16_t duty_cycle = 0;
    int16_t delta = 100;
    lld_bb_init_driver();
    debug_stream_init();
    //systime_t time = chVTGetSystemTime();
    while(1)
    {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
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
        if(duty_cycle > 0)
            lld_set_diver_bb_direct(duty_cycle, wheel);
    	else if (duty_cycle < 0)
    	    lld_set_diver_bb_reverse((PWM_PERIOD+duty_cycle),wheel);
        else
            lld_set_diver_bb_off(wheel);
	dbgprintf("duty_cycle:%d\n\r",(int)duty_cycle);
	//time = chThdSleepUntilWindowed (time, TIME_MS2I(200)+time);
    }
}






#include <test.h>
#include <lld_control_servo.h>
#include <serial.h>
#include <common.h>

void test_lld_nonlinear(type_servo servo)
{
      int16_t delta = 50;
      int16_t duty_cycle = 0;
      int16_t high = 0;
      int16_t low = 0;
      lld_control_servo_init();
      debug_stream_init();
      systime_t time = chVTGetSystemTime();

    while(1)
    {
        high = get_servo_high_limit(servo);
        low = get_servo_low_limit(servo);
        for(duty_cycle = low; duty_cycle <= high; duty_cycle += delta)
        {
            duty_cycle = CLIP_VALUE(duty_cycle,low,high);
            lld_set_dutycycle_servo(duty_cycle, servo);
            dbgprintf("duty_cycle:%d\n\r",(int)duty_cycle);
            //delay for fixing the angle
            time = chThdSleepUntilWindowed (time, TIME_MS2I(4000)+time);

        }
       for(duty_cycle = high; duty_cycle >= low; duty_cycle -= delta)
       {
           duty_cycle = CLIP_VALUE(duty_cycle,low,high);
           lld_set_dutycycle_servo(duty_cycle, servo);
           dbgprintf("duty_cycle:%d\n\r",(int)duty_cycle);
           //delay for fixing the angle
           time = chThdSleepUntilWindowed (time, TIME_MS2I(4000)+time);
       }
    }

}

#include <arm_driver.h>
#include <test.h>
#include <serial.h>
#include <encoder.h>

#define up_period   	5000
#define down_period 	5000


void test_arm(void)
{
    ARM_DRIVER_init();
    Encoder_init();
    debug_stream_init();


    ARM_up(RIGHT_ARM, up_period);
    chThdSleepSeconds(5);
    dbgprintf("%.4f\r\n", Encoder_Read());
    Off_ARM(RIGHT_ARM);


    ARM_down(RIGHT_ARM, down_period);
    chThdSleepSeconds(5);
    dbgprintf("%.4f\r\n", Encoder_Read());
    Off_ARM(RIGHT_ARM);
}

#include <arm_driver.h>
#include <test.h>
#include <serial.h>
#include <encoder.h>

#define up_period   	3000
#define down_period 	3000


void test_arm(void)
{
    ARM_DRIVER_init();
    Encoder_init();
    debug_stream_init();


    ARM_up(LEFT_ARM, up_period);
    chThdSleepSeconds(3);
    dbgprintf("%.4f\r\n", Encoder_Read());
    Off_ARM(LEFT_ARM);


    ARM_down(LEFT_ARM, down_period);
    chThdSleepSeconds(3);
    dbgprintf("%.4f\r\n", Encoder_Read());
    Off_ARM(LEFT_ARM);
}

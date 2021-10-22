#include <close_sys_arm.h>
#include <test.h>
#include <serial.h>
#include <encoder.h>
#include <arm_driver.h>


void test_close_sys(void)
{
    Encoder_init();
    ARM_DRIVER_init();
    debug_stream_init();
    double angle = 10;
    close_right_arm(angle);
}

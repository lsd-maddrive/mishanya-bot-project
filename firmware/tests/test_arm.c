#include <arm_driver.h>
#include <test.h>

#define up_period   	3000
#define down_period 	3000


void test_arm(void)
{
    ARM_DRIVER_init();

    ARM_up(RIGHT_ARM, up_period);
    chThdSleepSeconds(2);
    Off_ARM(RIGHT_ARM);

    ARM_down(RIGHT_ARM, down_period);
    chThdSleepSeconds(2);
    Off_ARM(RIGHT_ARM);
}

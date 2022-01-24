#include <elbow_driver.h>
#include <test.h>
#include "serial.h"




void test_arm(void)
{

elbow_init();

elbow_up(LEFT, 100);
chThdSleepMilliseconds(5000);
elbow_off(LEFT);


}

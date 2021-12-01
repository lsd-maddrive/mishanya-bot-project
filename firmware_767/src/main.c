#include <test.h>

static void testsRoutines(void)
{
    #if(MAIN_PROGRAM == PROGRAM_TEST_SERVO_LEFT_HAND)
        test_lld_servo_left_hand(&left_wrist);
    #endif
}


int main(void)
{
    halInit();
    chSysInit();
    #if(MAIN_PROGRAM!=PROGRAM_MASTER)
        testsRoutines();
    #endif
}

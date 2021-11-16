#include <test.h>

static void testsRoutines(void)
{
    #if(MAIN_PROGRAM == PROGRAM_TEST_ENCODER)
        test_abs_encoder();
    #elif(MAIN_PROGRAM == PROGRAM_TEST_SERVO_HAND)
	test_lld_servo_hand();
    #elif(MAIN_PROGRAM == PROGRAM_TEST_SERVO_WRIST)
	test_lld_servo_wrist();
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

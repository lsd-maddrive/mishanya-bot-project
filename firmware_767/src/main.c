#include <test.h>

static void testsRoutines(void)
{
    #if(MAIN_PROGRAM == PROGRAM_TEST_SERVO_LEFT_HAND)
        test_lld_servo_left_hand();
    #elif(MAIN_PROGRAM == PROGRAM_TEST_SERVO_RIGHT_HAND)
        test_lld_servo_right_hand();
    #elif(MAIN_PROGRAM == PROGRAM_TEST_SERVO_LEFT_WRIST)
        test_lld_servo_left_wrist();
    #elif(MAIN_PROGRAM == PROGRAM_TEST_SERVO_RIGHT_WRIST)
        test_lld_servo_right_wrist();
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

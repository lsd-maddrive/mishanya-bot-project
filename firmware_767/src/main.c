#include <common.h>
#include <test.h>

static void testsRoutines(void)
{
    #if(MAIN_PROGRAM == PROGRAM_TEST_SERVO_LEFT_HAND)
        test_lld_servo(LEFT_HAND);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_SERVO_LEFT_WRIST)
        test_lld_servo(LEFT_WRIST);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_SERVO_RIGHT_HAND)
        test_lld_servo(RIGHT_HAND);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_SERVO_RIGHT_WRIST)
       test_lld_servo(RIGHT_WRIST);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_SERVO_NONLINEAR)
       test_lld_nonlinear(LEFT_WRIST);
    #elif(MAIN_PROGRAM==PROGRAM_TEST_ELBOW_DRIVER)
        test_elbow();
    #elif(MAIN_PROGRAM==PROGRAM_TEST_ARM_CONTROL_SYSTEM)
        test_arm_control_system();
    #elif(MAIN_PROGRAM==PROGRAM_TEST_ENCODER)
        test_abs_encoder();
    #endif
}

int main(void)
{
    halInit();
    chSysInit();
    #if(MAIN_PROGRAM != PROGRAM_MASTER)
        testsRoutines();
    #endif
}

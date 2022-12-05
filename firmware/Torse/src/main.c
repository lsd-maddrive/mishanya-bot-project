#include <common.h>
#include <test.h>
#include "arm_tasks.h"

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
    #elif(MAIN_PROGRAM==PROGRAM_TEST_ARM_HIGH_FUNCTION)
      test_arm_high_function();
    #elif(MAIN_PROGRAM==PROGRAM_TEST_ARM_CONTROL_SYSTEM)
      test_arm_control_system();
    #elif(MAIN_PROGRAM==PROGRAM_TEST_ARM_KINEMATIC)
      test_arm_kinematic();
    #elif(MAIN_PROGRAM==PROGRAM_TEST_ARM_ENCODER)
        test_arm_encoder();
    #elif(MAIN_PROGRAM==PROGRAM_TEST_PID)
      test_PID();
    #endif
}

int main(void)
{
  halInit();
  chSysInit();
  init_low_level();
  arm_tasks_init();
  #if(MAIN_PROGRAM != PROGRAM_MASTER)
    testsRoutines();
  #endif
}

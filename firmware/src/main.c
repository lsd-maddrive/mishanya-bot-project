#include <test.h>

static void testsRoutines(void)
{

  #if(MAIN_PROGRAM==PROGRAM_TEST_LEFT_ELBOW_ENCODER)
    test_elbow_encoder(LEFT);
  #endif

  #if(MAIN_PROGRAM==PROGRAM_TEST_RIGHT_ELBOW_ENCODER)
    test_elbow_encoder(RIGHT);
  #endif

  #if(MAIN_PROGRAM==PROGRAM_TEST_ELBOW_DRIVER)
    test_elbow();
  #endif

  #if(MAIN_PROGRAM==PROGRAM_TEST_PID)
    test_PID();
  #endif

  #if(MAIN_PROGRAM==PROGRAM_TEST_ARM_CONTROL_SYSTEM)
    test_arm_control_system();
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

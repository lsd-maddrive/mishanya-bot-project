#include <test.h>

static void testsRoutines(void)
{

  #if(MAIN_PROGRAM==PROGRAM_TEST_ENCODER)
    test_abs_encoder();
  #endif

  #if(MAIN_PROGRAM==PROGRAM_TEST_ELBOW_DRIVER)
    test_elbow();
  #endif

  #if(MAIN_PROGRAM==PROGRAM_TEST_NORMALIZE)
    test_normalize();
  #endif

  #if(MAIN_PROGRAM==PROGRAM_TEST_PID)
    test_PID();
  #endif

  #if(MAIN_PROGRAM==PROGRAM_TEST_ARM_CLOSE_SYS)
    test_close_sys();
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

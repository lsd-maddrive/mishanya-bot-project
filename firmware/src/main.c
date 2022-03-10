#include <test.h>

static void testsRoutines(void)
{

  #if(MAIN_PROGRAM==PROGRAM_TEST_ENCODER)
    test_abs_encoder();
  #endif

  #if(MAIN_PROGRAM==PROGRAM_TEST_ARM_DRIVER)
    test_elbow();
  #endif

  #if(MAIN_PROGRAM==PROGRAM_TEST_LLD_BB)
    test_lld_bb();
  #endif

  #if(MAIN_PROGRAM==PROGRAM_TEST_LLD_RED)
    test_lld_red();
  #endif

  #if(MAIN_PROGRAM==PROGRAM_TEST_NORMALIZE)
    test_normalize();
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

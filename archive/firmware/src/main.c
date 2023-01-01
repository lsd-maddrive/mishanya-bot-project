#include <test.h>

static void testsRoutines(void)
{

#if(MAIN_PROGRAM==PROGRAM_TEST_ENCODER)
<<<<<<< HEAD:archive/firmware/src/main.c
    test_abs_encoder();
=======
    test_elbow_encoder();
>>>>>>> develop:firmware/src/main.c
#endif

#if(MAIN_PROGRAM==PROGRAM_TEST_ARM_DRIVER)
    test_elbow();
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

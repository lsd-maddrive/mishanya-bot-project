#include <test.h>

static void testsRoutines(void)
{

  #if(MAIN_PROGRAM==PROGRAM_TEST_LEFT_ELBOW_ENCODER)
    extern arm_encoder_t left_elbow_encoder;
    test_arm_encoder(&left_elbow_encoder);
  #endif

#if(MAIN_PROGRAM==PROGRAM_TEST_RIGHT_ELBOW_ENCODER)
    extern arm_encoder_t right_elbow_encoder;
    test_arm_encoder(&right_elbow_encoder);
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

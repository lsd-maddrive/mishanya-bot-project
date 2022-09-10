#include <common.h>
#include <test.h>

static void testsRoutines(void)
{
    #if(MAIN_PROGRAM==PROGRAM_TEST_ENCODER_BASE_ALL)
        test_encoder_base_all();
    #elif(MAIN_PROGRAM==PROGRAM_TEST_ENCODER_BASE_1)
        test_encoder_base(ENCODER_1);
    #elif(MAIN_PROGRAM==PROGRAM_TEST_ENCODER_BASE_2)
       test_encoder_base(ENCODER_2);
    #elif(MAIN_PROGRAM==PROGRAM_TEST_ENCODER_BASE_3)
       test_encoder_base(ENCODER_3);
    #elif(MAIN_PROGRAM==PROGRAM_TEST_ODOMETRY_BASE)
       testOdometryBase();
    #elif(MAIN_PROGRAM==PROGRAM_TEST_ODOMETRY_BASE_ALL)
       testOdometryBaseAll();
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

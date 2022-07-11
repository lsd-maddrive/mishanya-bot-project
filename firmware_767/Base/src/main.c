#include <common.h>
#include <test.h>

static void testsRoutines(void)
{
    #if(MAIN_PROGRAM==PROGRAM_TEST_ENCODER_BASE)
        test_encoder_base();
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

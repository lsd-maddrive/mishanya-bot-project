#include <test.h>

static void search_test(void)
{
	#if(MAIN_PROGRAM==PROGRAM_ENCODER)
		test_abs_encoder();
	#endif
}




int main(void)
{
	debug_stream_init();
    halInit();
    chSysInit();
	#if(MAIN_PROGRAM!=PROGRAM_MASTER)
		search_test();
	#endif


}

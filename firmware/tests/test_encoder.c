#include <encoder.h>
#include <serial.h>
#include <test.h>


void test_abs_encoder(void)
{
	float angle = 0;
	Encoder_init();
	debug_stream_init();

    while (1)
    {
    	chThdSleepMilliseconds(100);
    	angle = Encoder_Read();
    	if(angle>=0)
    		dbgprintf("angle=%.4f\r\n", angle);


    }
}

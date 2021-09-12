#include <encoder.h>
#include <serial.h>
#include <test.h>


void test_abs_encoder(void)
{
	int angle = 0;
	SPI_init();
	debug_stream_init();

    while (1)
    {
    	chThdSleepMilliseconds(100);
    	angle = SPI_RX();
    	if(angle>=0)
    		dbgprintf("angle=%d\r\n", angle);


    }
}


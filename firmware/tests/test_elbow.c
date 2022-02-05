#include <elbow_driver.h>
#include <test.h>
#include "serial.h"


void test_elbow(void)
{
char rcv_data;
uint8_t arm = 0;
uint8_t test = 0;
int16_t period = 0;
debug_stream_init();
elbow_init();
elbow_off(RIGHT);
elbow_off(LEFT);
while(1)
{
	dbgprintf("--------------------\r\n");
	dbgprintf("elbow side(r - right; l - left):\r\n");
	rcv_data = sdGet(&SD2);
	switch (rcv_data)
	{
		case 'r':
			arm = RIGHT;
			dbgprintf("RIGHT ARM\r\n");
			dbgprintf("--------------------\r\n");
			dbgprintf("\r\n");
			break;

		case 'l':
			arm = LEFT;
			dbgprintf("LEFT ARM\r\n");
			dbgprintf("--------------------\r\n");
			dbgprintf("\r\n");
			break;

		default:
			break;
	}

	test = 0;

	while(!test)
	{
		if(period>0)
			elbow_up(arm, period);
		else if(period<0)
			elbow_down(arm, period*-1);
		else
			elbow_off(arm);

		dbgprintf("--------------------\r\n");
		dbgprintf("PWM period(z: +500, x: -500):\r\n");
		rcv_data = sdGet(&SD2);
		switch (rcv_data)
		{
			case 'z':
				period += 500;
				if(period > 10000)
					period = 10000;
				break;

			case 'x':
				period -= 500;
				if(period < -10000)
					period = -10000;
				break;

			case 'b':
				test = 1;
				elbow_off(arm);
				period = 0;
				break;

			default:
				break;
		}
		dbgprintf("PWM period=%d\r\n", period);
		dbgprintf("--------------------\r\n");
		dbgprintf("\r\n");


	}
}


}

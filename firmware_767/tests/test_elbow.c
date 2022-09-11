#include "elbow_driver.h"
#include "test.h"
#include "serial.h"


void test_elbow(void)
{
//	char rcv_data;
//	uint8_t arm = 0;
//	uint8_t test = 0;
//	int16_t period = 0;
//
//	debug_stream_init();
//	elbow_init();
//
//	elbow_off(LEFT_ELBOW);
//	elbow_off(LEFT_SHOULDER_IN);
//	elbow_off(LEFT_SHOULDER_OUT);
//
//	elbow_off(RIGHT_ELBOW);
//	elbow_off(RIGHT_SHOULDER_IN);
//	elbow_off(RIGHT_SHOULDER_OUT);
//
//	while (1)
//	{
//		dbgprintf("--------------------\r\n");
//		dbgprintf(
//			"part arm(1 - right elbow; 2 - left elbow; 3-left shoulder_in; "
//    		"4-right shoulder_in; 5-left shoulder_out; 6-right shoulder_out):\r\n"
//		);
//
//		// waiting for input
//		rcv_data = sdGet(&SD3);
//		switch (rcv_data)
//		{
//			case '1':
//				arm = RIGHT_ELBOW;
//				dbgprintf("1\r\n");
//				dbgprintf("--------------------\r\n");
//				dbgprintf("\r\n");
//				break;
//
//			case '2':
//			  	arm = LEFT_ELBOW;
//			  	dbgprintf("2\r\n");
//			  	dbgprintf("--------------------\r\n");
//			  	dbgprintf("\r\n");
//			  	break;
//			case '3':
//				arm = LEFT_SHOULDER_IN;
//				dbgprintf("3\r\n");
//				dbgprintf("--------------------\r\n");
//				dbgprintf("\r\n");
//				break;
//			case '4':
//				arm = RIGHT_SHOULDER_IN;
//				dbgprintf("4\r\n");
//				dbgprintf("--------------------\r\n");
//				dbgprintf("\r\n");
//				break;
//			case '5':
//				arm = LEFT_SHOULDER_OUT;
//				dbgprintf("5\r\n");
//				dbgprintf("--------------------\r\n");
//				dbgprintf("\r\n");
//				break;
//			case '6':
//			   arm = RIGHT_SHOULDER_OUT;
//			   dbgprintf("6\r\n");
//			   dbgprintf("--------------------\r\n");
//			   dbgprintf("\r\n");
//			   break;
//
//		  default:
//			   break;
//		}
//
//		test = 0;
//
//		while (!test)
//		{
//			if (period > 0)
//			{
//				elbow_up(arm, period);
//			}
//			else if(period < 0)
//			{
//				elbow_down(arm, period*-1);
//			}
//			else
//			{
//				elbow_off(arm);
//			}
//			dbgprintf("--------------------\r\n");
//			dbgprintf("PWM period(z: +500, x: -500):\r\n");
//			dbgprintf("b: change elbow side\r\n");
//
//			rcv_data = sdGet(&SD3);
//			switch (rcv_data)
//			{
//				case 'z':
//					period += 500;
//					if(period > 10000)
//					period = 10000;
//					break;
//
//				case 'x':
//					period -= 500;
//					if(period < -10000)
//					period = -10000;
//					break;
//
//				case 'b':
//					test = 1;
//					elbow_off(arm);
//					period = 0;
//					break;
//
//				default:
//					break;
//			}
//			dbgprintf("PWM period=%d\r\n", period);
//			dbgprintf("--------------------\r\n");
//			dbgprintf("\r\n");
//    	}
//	}
}

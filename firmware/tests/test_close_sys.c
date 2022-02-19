#include <close_sys_arm.h>
#include <test.h>
#include <serial.h>
#include <encoder.h>
#include <elbow_driver.h>
#include <stdlib.h>


void test_close_sys(void)
{
	char rcv_data;
	uint8_t buf[2];
	uint8_t arm = 0;
	uint8_t angle = 0;
	debug_stream_init();
  elbow_init();
  Encoder_init();
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

    dbgprintf("--------------------\r\n");
    dbgprintf("set angle(0-40):\r\n");
    sdRead(&SD2, buf, 2);
    angle = atoi(buf);
    dbgprintf("goal angle=%d\r\n", angle);
    elbow_set_angle(angle, arm);
  }

}

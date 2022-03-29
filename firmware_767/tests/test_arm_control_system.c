#include "arm_control_system.h"
#include "test.h"
#include "serial.h"
#include "encoder.h"
#include "elbow_driver.h"
#include <stdlib.h>

static THD_WORKING_AREA(traking_elbow,256);

static THD_FUNCTION(elbow_update,arg) {
  (void *) arg;
  systime_t time = chVTGetSystemTimeX();
  while (1) {
    elbow_update_angle(0.00002);
    time = chThdSleepUntilWindowed(time, TIME_MS2I(20)+time);
  }

}



void test_arm_control_system(void)
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

  chThdCreateStatic(traking_elbow,sizeof(traking_elbow),NORMALPRIO-1,
                    elbow_update, NULL);


  while(1)
  {
    dbgprintf("--------------------\r\n");
    dbgprintf("elbow side(r - right; l - left):\r\n");
    rcv_data = sdGet(&SD3);

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
    dbgprintf("set angle(00-40):\r\n");
    sdRead(&SD3, buf, 2);
    angle = atoi(buf);
    dbgprintf("goal angle=%d\r\n", angle);
    elbow_set_angle((float)angle, arm);
  }

}

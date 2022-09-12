#include "arm_control_system.h"
#include "test.h"
#include "serial.h"
#include "arm_encoder.h"
#include "elbow_driver.h"
#include <stdlib.h>

static THD_WORKING_AREA(traking_elbow,256);

static THD_FUNCTION(elbow_update,arg) {
  (void) arg;
  systime_t time = chVTGetSystemTimeX();
  while (1) {
    elbow_update_angle(0.00002);
    time = chThdSleepUntilWindowed(time, TIME_MS2I(20)+time);
  }

}


void test_arm_control_system(void)
{
//  char rcv_data;
//  uint8_t buf[2];
//  uint8_t arm = 0;
//  uint8_t angle = 0;
//
//  debug_stream_init();
//  elbow_init();
//  elbow_off(LEFT);
//  elbow_off(RIGHT);
//
//  chThdCreateStatic(traking_elbow,sizeof(traking_elbow),NORMALPRIO-2,
//                    elbow_update, NULL);
//
//
//  while(1)
//  {
//    dbgprintf("--------------------\r\n");
//    dbgprintf(
//             "part arm(1 - right elbow; 2 - left elbow; 3-left shoulder_in; "
//             "4-right shoulder_in; 5-left shoulder_out; 6-right shoulder_out):\r\n"
//    );
//    rcv_data = sdGet(&SD3);
//
//    switch (rcv_data)
//    {
//    case '1':
//                    arm = RIGHT_ELBOW;
//                    dbgprintf("1\r\n");
//                    dbgprintf("--------------------\r\n");
//                    dbgprintf("\r\n");
//                    break;
//
//                case '2':
//                    arm = LEFT_ELBOW;
//                    dbgprintf("2\r\n");
//                    dbgprintf("--------------------\r\n");
//                    dbgprintf("\r\n");
//                    break;
//                case '3':
//                    arm = LEFT_SHOULDER_IN;
//                    dbgprintf("3\r\n");
//                    dbgprintf("--------------------\r\n");
//                    dbgprintf("\r\n");
//                    break;
//                case '4':
//                    arm = RIGHT_SHOULDER_IN;
//                    dbgprintf("4\r\n");
//                    dbgprintf("--------------------\r\n");
//                    dbgprintf("\r\n");
//                    break;
//                case '5':
//                    arm = LEFT_SHOULDER_OUT;
//                    dbgprintf("5\r\n");
//                    dbgprintf("--------------------\r\n");
//                    dbgprintf("\r\n");
//                    break;
//                case '6':
//                   arm = RIGHT_SHOULDER_OUT;
//                   dbgprintf("6\r\n");
//                   dbgprintf("--------------------\r\n");
//                   dbgprintf("\r\n");
//                   break;
//
//              default:
//                   break;
//    }
//
//    dbgprintf("--------------------\r\n");
//    dbgprintf("set angle(00-40):\r\n");
//    sdRead(&SD3, buf, 2);
//    angle = atoi((char*)buf);
//    dbgprintf("goal angle=%d\r\n", angle);
//    elbow_set_angle((float)angle, arm);
//  }

}

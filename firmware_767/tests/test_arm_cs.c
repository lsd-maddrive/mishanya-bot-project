#include "arm_control_system.h"
#include "test.h"
#include "serial.h"
#include "arm_encoder.h"
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


void test_arm_cs(void)
{
//  char rcv_data;
//  uint8_t buf[2];
//  uint8_t arm_1 = 0;
//  uint8_t arm_2 = 0;
//  uint8_t arm_3 = 0;
//  uint8_t angle_1 = 0;
//  uint8_t angle_2 = 0;
//  uint8_t angle_3 = 0;
//
//  debug_stream_init();
//  elbow_init();
//  elbow_off(LEFT_ELBOW);
//  elbow_off(LEFT_SHOULDER_IN);
//  elbow_off(LEFT_SHOULDER_OUT);
//  elbow_off(RIGHT_ELBOW);
//  elbow_off(RIGHT_SHOULDER_IN);
//  elbow_off(RIGHT_SHOULDER_OUT);
//
//  chThdCreateStatic(traking_elbow,sizeof(traking_elbow),NORMALPRIO-2,
//                    elbow_update, NULL);
//
//
//  while(1)
//  {
//    dbgprintf("--------------------\r\n");
//    dbgprintf("part arm(1 - right arm; 2 - left arm):\r\n");
//    rcv_data = sdGet(&SD3);
//
//    switch (rcv_data)
//    {
//                case '1':
//                    arm_1 = RIGHT_ELBOW;
//                    arm_2 = RIGHT_SHOULDER_OUT;
//                    arm_3 = RIGHT_SHOULDER_IN;
//                    dbgprintf("1\r\n");
//                    dbgprintf("--------------------\r\n");
//                    dbgprintf("\r\n");
//                    break;
//
//                case '2':
//                    arm_1 = LEFT_ELBOW;
//                    arm_2 = LEFT_SHOULDER_OUT;
//                    arm_3 = LEFT_SHOULDER_IN;
//                    dbgprintf("2\r\n");
//                    dbgprintf("--------------------\r\n");
//                    dbgprintf("\r\n");
//                    break;
//
//              default:
//                   break;
//    }
//
//    dbgprintf("--------------------\r\n");
//    dbgprintf("set angle elbow(00-40):\r\n");
//    sdRead(&SD3, buf, 2);
//    angle_1 = atoi((char*)buf);
//    dbgprintf("goal angle=%d\r\n", angle_1);
//    dbgprintf("set angle shoulder_out(00-52):\r\n");
//    sdRead(&SD3, buf, 2);
//    angle_2 = atoi((char*)buf);
//    dbgprintf("goal angle=%d\r\n", angle_2);
//    dbgprintf("set angle shoulder in(00-60):\r\n");
//    sdRead(&SD3, buf, 2);
//    angle_3 = atoi((char*)buf);
//    dbgprintf("goal angle=%d\r\n", angle_3);
//    elbow_set_angle((float)angle_1, arm_1);
//    elbow_set_angle((float)angle_2, arm_2);
//    elbow_set_angle((float)angle_3, arm_3);
//  }
}

#include "arm_control_system.h"
#include "test.h"
#include "serial.h"
#include "elbow_driver.h"
#include "horizontal_shoulder_driver.h"
#include "vertical_shoulder_driver.h"
#include <stdlib.h>

static THD_WORKING_AREA(traking_elbow,256);
static THD_WORKING_AREA(traking_v_shoulder,256);
static THD_WORKING_AREA(traking_h_shoulder,256);


typedef struct {
    void (* set_angle) (float target_angle, arm_side_t side);
} acs_test_t;



static THD_FUNCTION(elbow_update,arg) {
  (void) arg;
  systime_t time = chVTGetSystemTimeX();
  while (1) {
    elbow_update_angle(0.00002f);
    time = chThdSleepUntilWindowed(time, TIME_MS2I(20)+time);
  }
}

static THD_FUNCTION(v_shoulder_update,arg) {
  (void) arg;
  systime_t time = chVTGetSystemTimeX();
  while (1) {
    v_shoulder_update_angle(0.00002f);
    time = chThdSleepUntilWindowed(time, TIME_MS2I(20)+time);
  }
}

static THD_FUNCTION(h_shoulder_update,arg) {
  (void) arg;
  systime_t time = chVTGetSystemTimeX();
  while (1) {
    h_shoulder_update_angle(0.00002f);
    time = chThdSleepUntilWindowed(time, TIME_MS2I(20)+time);
  }
}


void test_arm_control_system(void)
{
  char rcv_data[2];
  arm_side_t side;
  uint8_t angle = 0;
  part_arm_type_t part_arm = NONE;
  acs_test_t acs[3];

  debug_stream_init();
  elbow_init();
  h_shoulder_init();
  v_shoulder_init();

  acs[ELBOW].set_angle = elbow_set_angle;

  acs[V_SHOULDER].set_angle = v_shoulder_set_angle;

  acs[H_SHOULDER].set_angle = h_shoulder_set_angle;



  chThdCreateStatic(traking_elbow,sizeof(traking_elbow),NORMALPRIO-2,
                    elbow_update, NULL);

  chThdCreateStatic(traking_v_shoulder,sizeof(traking_v_shoulder),NORMALPRIO-2,
                    v_shoulder_update, NULL);

  chThdCreateStatic(traking_h_shoulder,sizeof(traking_h_shoulder),NORMALPRIO-2,
                    h_shoulder_update, NULL);


  while(1)
  {
    dbgprintf(
            "///////////////////////////////////\r\n"
            "//        choose part arm:       //\r\n"
            "//1 - elbow                      //\r\n"
            "//2 - vertical shoulder          //\r\n"
            "//3 - horizontal shoulder        //\r\n"
            "///////////////////////////////////\r\n"
            "your choose: "
    );

    // waiting for input
    rcv_data[0] = sdGet(&SD3);
    switch (rcv_data[0]) {
      case '1': {
        dbgprintf("elbow\r\n\r\n");
        part_arm = ELBOW;
      }
        break;
      case '2': {
        dbgprintf("vertical shoulder\r\n\r\n");
        part_arm = V_SHOULDER;
      }
        break;
      case '3': {
        dbgprintf("horizontal shoulder\r\n\r\n");
        part_arm = H_SHOULDER;
      }
        break;
      default: {
        dbgprintf("wrong\r\n\r\n");
        part_arm = NONE;
      }
        break;
    }

    while (part_arm != NONE) {
      dbgprintf(
              "///////////////////////////////////\r\n"
              "//        choose side:           //\r\n"
              "//1 - left                       //\r\n"
              "//2 - right                      //\r\n"
              "//any - break                    //\r\n"
              "///////////////////////////////////\r\n"
              "your choose: "
      );

      rcv_data[0] = sdGet(&SD3);
      switch (rcv_data[0]) {
        case '1': {
          dbgprintf("left side\r\n");
          side = LEFT;
        }
          break;
        case '2': {
          dbgprintf("right side\r\n");
          side = RIGHT;
        }
          break;
        default: {
          dbgprintf("back to choose part arm\r\n\r\n");
          part_arm = NONE;
          side = NONE_SIDE;
        }
          break;
      }
      if(side != NONE_SIDE)
      {
        dbgprintf("set angle(00-40):\r\n");
        sdRead(&SD3, (uint8_t*)rcv_data, 2);
        angle = (uint8_t)atoi(rcv_data);
        dbgprintf("goal angle = %d\r\n\r\n", angle);
        acs[part_arm].set_angle((float)angle, side);
      }
    }
  }
}

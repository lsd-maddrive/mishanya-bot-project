#include "test.h"
#include "serial.h"
#include "arms.h"
#include "stdbool.h"

coord_t target_coordinates[5] = {
        {
                .x = 0.3f,
                .y = 0.3f,
                .z = 0.0f
        },
        {
                .x = 0.25f,
                .y = 0.35f,
                .z = 0.1f
        },
        {
                .x = 0.3f,
                .y = 0.2f,
                .z = 0.1f
        },
        {
                .x = 0.3f,
                .y = 0.3f,
                .z = 0.1f
        },
        {
                .x = 0.3f,
                .y = 0.2f,
                .z = 0.15f
        },
};


void test_arm_kinematic(void)
{
  debug_stream_init();
  arms_init();
  size_t i = 0;
  char rcv_data;
  while (1) {
    dbgprintf(
            "///////////////////////////////////\r\n"
            "//        choose:                //\r\n"
            "//1 - next point                 //\r\n"
            "//2 - stop                       //\r\n"
            "///////////////////////////////////\r\n"
            "your choose: "
    );

    // waiting for input
    rcv_data = sdGet(&SD3);

    switch (rcv_data) {
      case '1': {
        dbgprintf("next point\r\n\r\n");
      }
        break;
      case '2': {
        dbgprintf("stop\r\n\r\n");
        return;
      }
      default:
        break;
    }

    if(elbow_get_status(RIGHT) && h_shoulder_get_status(RIGHT) && v_shoulder_get_status(RIGHT))
    {
      arm_set_coordinates(RIGHT, &target_coordinates[i]);
      i++;
      if(i>4)
        i = 0;
    }
  }

}
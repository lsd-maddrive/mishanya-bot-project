#include "test.h"
#include "serial.h"
#include "control_system_handler.h"

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
  size_t i = 0;
  char rcv_data;
  while (1) {
    dbgprintf(&SD3,
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
        dbgprintf(&SD3, "next point\r\n\r\n");
      }
        break;
      case '2': {
        dbgprintf(&SD3, "stop\r\n\r\n");
        return;
      }
      default:
        break;
    }

    if(elbow_get_status(RIGHT) && h_shoulder_get_status(RIGHT) && v_shoulder_get_status(RIGHT))
    {
        control_system_handler_set_coordinates(RIGHT, &target_coordinates[i]);
      i++;
      if(i>4)
        i = 0;
    }
  }

}
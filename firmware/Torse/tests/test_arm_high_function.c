#include "elbow_driver.h"
#include "horizontal_shoulder_driver.h"
#include "vertical_shoulder_driver.h"
#include "low_level.h"
#include "test.h"
#include "serial.h"
#include "stdlib.h"


typedef struct {
    void (* up) (arm_side_t, uint16_t);
    void (* down) (arm_side_t, uint16_t);
    void (* off) (arm_side_t);
} high_func_test_t;


void test_arm_high_function(void)
{
	uint8_t rcv_data;
  part_arm_t part_arm = NONE;
  arm_side_t side;
  int16_t period = 0;
  high_func_test_t high_func[3];

  high_func[ELBOW].down = elbow_down;
  high_func[ELBOW].up = elbow_up;
  high_func[ELBOW].off = elbow_off;

  high_func[V_SHOULDER].down = v_shoulder_down;
  high_func[V_SHOULDER].up = v_shoulder_up;
  high_func[V_SHOULDER].off = v_shoulder_off;

  high_func[H_SHOULDER].down = h_shoulder_down;
  high_func[H_SHOULDER].up = h_shoulder_up;
  high_func[H_SHOULDER].off = h_shoulder_off;

	debug_stream_init();
	elbow_init();
  h_shoulder_init();
  v_shoulder_init();

  for(size_t i = 0; i<3; i++)
  {
    high_func[i].off(LEFT);
    high_func[i].off(RIGHT);
  }

	while (1) {
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
    rcv_data = sdGet(&SD3);
    switch (rcv_data) {
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

      rcv_data = sdGet(&SD3);
      switch (rcv_data) {
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
      while (side != NONE_SIDE) {
        if (period > 0) {
          high_func[part_arm].up(side, period);
        } else if (period < 0) {
          high_func[part_arm].down(side, period * (-1));
        } else {
          high_func[part_arm].off(side);
        }

        dbgprintf("\r\n\r\n........................\r\n");
        dbgprintf("PWM period=%d\r\n", period);
        dbgprintf("........................\r\n");
        dbgprintf("///////////////////////////////////\r\n"
                  "//            control:           //\r\n"
                  "//1 - pwm period +500            //\r\n"
                  "//2 - pwm period -500            //\r\n"
                  "//any - break                    //\r\n"
                  "///////////////////////////////////\r\n"
                  "your choose: ");

        rcv_data = sdGet(&SD3);
        switch (rcv_data) {
          case '1': {
            period += 500;
            if (period > 10000)
              period = 10000;
          }
            break;

          case '2': {
            period -= 500;
            if (period < -10000)
              period = -10000;
          }
            break;

          default: {
            high_func[part_arm].off(side);
            side = NONE_SIDE;
            dbgprintf("back to choose side\r\n\r\n");
          }
            break;
        }
      }
    }
  }

}

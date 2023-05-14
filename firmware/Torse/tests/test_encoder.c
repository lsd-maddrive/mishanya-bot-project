#include "elbow_driver.h"
#include "horizontal_shoulder_driver.h"
#include "vertical_shoulder_driver.h"
#include "low_level.h"
#include "test.h"
#include "serial.h"
#include "stdlib.h"


typedef struct {
    float (* encoder_read) (arm_side_t);
} arm_enc_test_t;


void test_arm_encoder(void)
{
  uint8_t rcv_data;
  arm_side_t side;
  float angle = 0;
  part_arm_type_t part_arm = NONE;
  arm_enc_test_t enc_read[3];

  enc_read[ELBOW].encoder_read = elbow_read_angle;

  enc_read[V_SHOULDER].encoder_read = v_shoulder_read_angle;

  enc_read[H_SHOULDER].encoder_read = h_shoulder_read_angle;

  while (1) {
    dbgprintf(&SD3,
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
        dbgprintf(&SD3, "elbow\r\n\r\n");
        part_arm = ELBOW;
      }
        break;
      case '2': {
        dbgprintf(&SD3, "vertical shoulder\r\n\r\n");
        part_arm = V_SHOULDER;
      }
        break;
      case '3': {
        dbgprintf(&SD3, "horizontal shoulder\r\n\r\n");
        part_arm = H_SHOULDER;
      }
        break;
      default: {
        dbgprintf(&SD3, "wrong\r\n\r\n");
        part_arm = NONE;
      }
        break;
    }

    while (part_arm != NONE) {
      dbgprintf(&SD3,
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
          dbgprintf(&SD3, "left side\r\n");
          side = LEFT;
        }
          break;
        case '2': {
          dbgprintf(&SD3, "right side\r\n");
          side = RIGHT;
        }
          break;
        default: {
          dbgprintf(&SD3, "back to choose part arm\r\n\r\n");
          part_arm = NONE;
          side = NONE_SIDE;
        }
          break;
      }

      while (sdGetTimeout(&SD3, 500) == -1 && side != NONE_SIDE) {
        angle = enc_read[part_arm].encoder_read(side);

        dbgprintf(&SD3, "angle=%.4f\r\n", angle);

        dbgprintf(&SD3, "press any button to exit\r\n\r\n");
      }

    }
  }
}
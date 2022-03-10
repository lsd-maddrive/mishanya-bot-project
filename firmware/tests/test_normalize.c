#include "close_sys_arm.h"
#include "test.h"
#include "serial.h"
#include "encoder.h"
#include <stdlib.h>


void test_normalize(void)
{
  debug_stream_init();
  Encoder_init();

  uint8_t buf[3];
  uint8_t rcv_data;
  float current_angle_norm = 0;

  normalize_angle_t arm_angle = {
    .max_norm_angle = 0,
    .min_norm_angle = 0,
    .shift = 0,
    .zero_cross = false
  };

  dbgprintf("minimum angle from interval:\r\n");
  sdRead(&SD2, buf, 3);
  float min_angle = atoi(buf);

  dbgprintf("maximum angle from interval:\r\n");
  sdRead(&SD2, buf, 3);
  float max_angle = atoi(buf);

  // convert the angle range so that it starts from zero
  normalize_interval(min_angle, max_angle, &arm_angle);

  dbgprintf("minimum normalized angle: %.4f\r\n", min_angle);
  dbgprintf("maximum normalized angle: %.4f\r\n", max_angle);

  while(1)
  {
    current_angle_norm = normalize_angle(min_angle, &arm_angle);

    dbgprintf("normalized angle: %.4f\r\n", current_angle_norm);

    dbgprintf("real angle: %.4f\r\n", Encoder_Read());

    dbgprintf("press 'b' to exit, any button to restart the test:\r\n");
    rcv_data = sdGet(&SD2);
    if(rcv_data == 'b')
      break;
  }





}

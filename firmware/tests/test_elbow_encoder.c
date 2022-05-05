#include <serial.h>
#include <test.h>
#include <arm_encoder.h>



void test_elbow_encoder(arm_side_t encoder_side)
{
  float angle = 0;
  arm_encoder_t encoder;
  encoder = elbow_get_encoder_ctx(encoder_side);
  encoder_init(&encoder);
  debug_stream_init();
  while (1)
  {
    chThdSleepMilliseconds(100);
    angle = encoder_read(&encoder);

    dbgprintf("angle=%.4f\r\n", angle);
  }

}

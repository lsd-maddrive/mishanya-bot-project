#include <serial.h>
#include <test.h>
#include <arm_encoder.h>



void test_arm_encoder(arm_encoder_t* encoder)
{

  float angle = 0;
  encoder_init(encoder);
  debug_stream_init();

  while (1)
  {
    chThdSleepMilliseconds(100);
    angle = encoder_read(encoder);

    dbgprintf("angle=%.4f\r\n", angle);
  }

}

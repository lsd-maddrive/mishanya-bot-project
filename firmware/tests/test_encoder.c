#include <serial.h>
#include <test.h>
#include <arm_encoder.h>



void test_abs_encoder(void)
{

  float angle = 0;
//  encoder_init();
  debug_stream_init();

  while (1)
  {
    chThdSleepMilliseconds(100);
//    angle = encoder_read();

    dbgprintf("angle=%.4f\r\n", angle);
  }

}

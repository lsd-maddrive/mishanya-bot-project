#include <serial.h>
#include <test.h>
#include <encoder.h>



void test_abs_encoder(void)
{

  float angle = 0;
  Encoder_init();
  debug_stream_init();

  while (1)
  {
    chThdSleepMilliseconds(100);
    angle = Encoder_Read();

    dbgprintf("angle=%.4f\r\n", angle);
  }

}

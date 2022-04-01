#include <arm_encoder.h>

/************ Status bits ************/

#define OCF 0b00000100
#define COF 0b00000010
#define LIN 0b00000001
#define MagINC 0b10000000
#define MagDEC 0b01000000
#define EvenPAR 0b01000000

/************ Status bits ************/


/**
 * @brief   Initialize periphery connected to encoder
 */
void encoder_init(arm_encoder_t* encoder)
{
  palSetLineMode(encoder->encoder_pins.cs_encoder, PAL_MODE_OUTPUT_PUSHPULL);
//  if(!(encoder->spi_use))
//  {
    palSetLineMode(encoder->encoder_pins.clk_encoder, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(encoder->encoder_pins.miso_encoder, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
    spiStart(encoder->encoder_ptr, &encoder->encoder_conf);
//  }
}

/**
 * @brief recieve data from encoder
 * @return  angle of rotation
 * @return error
 */
float encoder_read(arm_encoder_t* encoder)
{
  uint8_t rx_encoder_buf[3] = {0};
  float angle = 0;

  spiSelect(encoder->encoder_ptr);
  spiReceive(encoder->encoder_ptr, 3, rx_encoder_buf);
  spiUnselect(encoder->encoder_ptr);

/*** check data ***/
  if((rx_encoder_buf[1]&OCF) && !(rx_encoder_buf[1]&COF) && !(rx_encoder_buf[1]&LIN))
  {
    rx_encoder_buf[1]=(rx_encoder_buf[1] >> 3) & 0b00011111;
    angle = rx_encoder_buf[1] | ((rx_encoder_buf[0] & 0b01111111) << 5);
    angle = (angle*360)/4096;
    return angle;
  }
  /*** error data ***/
  else
    return -1;
}






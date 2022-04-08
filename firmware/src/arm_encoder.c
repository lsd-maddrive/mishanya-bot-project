#include <arm_encoder.h>

#define FULL_TURN 360
#define BIT_DEPTH 4096 // 12 bit
#define FIRST_BYTE_MASK 0b01111111
#define SECOND_BYTE_MASK 0b00011111
#define FIRST_BYTE_SHIFT 5
#define SECOND_BYTE_SHIFT 3

/************ Status bits ************/

#define OCF 0b00000100
#define COF 0b00000010
#define LIN 0b00000001
#define MagINC 0b10000000
#define MagDEC 0b01000000
#define EvenPAR 0b01000000

/************ Status bits ************/


/**
 * @details initialize periphery connected to encoder
 * @param[in] encoder - pointer to the encoder structure
 */
void encoder_init(arm_encoder_t* encoder)
{
  palSetLineMode(encoder->encoder_pins.cs_encoder, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(encoder->encoder_pins.clk_encoder, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
  palSetLineMode(encoder->encoder_pins.miso_encoder, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
  spiStart(encoder->encoder_ptr, &encoder->encoder_conf);
}


/**
 * @details returns the current angle
 * @param[in] encoder - pointer to the encoder structure
 * @param[out] angle - current angle or error (-1)
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
    rx_encoder_buf[1]=(rx_encoder_buf[1] >> SECOND_BYTE_SHIFT) & SECOND_BYTE_MASK;
    angle = rx_encoder_buf[1] | ((rx_encoder_buf[0] & FIRST_BYTE_MASK) << FIRST_BYTE_SHIFT);
    angle = (angle*FULL_TURN)/BIT_DEPTH;
    return angle;
  }
  /*** error data ***/
  else
    return -1;
}






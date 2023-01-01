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
 * @details initialize periphery connected to encoder
 * @param[in] encoder - pointer to the encoder structure
 */
void encoder_init(arm_encoder_t* encoder,
                  ioline_t cs, ioline_t clk, ioline_t miso,
                  SPIDriver* spi_ptr)
{
  encoder->encoder_pins.cs_encoder = cs;
  encoder->encoder_pins.clk_encoder = clk;
  encoder->encoder_pins.miso_encoder = miso;
  encoder->encoder_ptr = spi_ptr;
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
  palWriteLine(encoder->encoder_pins.cs_encoder, PAL_LOW);
  spiReceive(encoder->encoder_ptr, 3, rx_encoder_buf);
  palWriteLine(encoder->encoder_pins.cs_encoder, PAL_HIGH);

  /*** check data ***/
  if((rx_encoder_buf[1]&OCF) && !(rx_encoder_buf[1]&COF) && !(rx_encoder_buf[1]&LIN))
  {
    rx_encoder_buf[1]=(rx_encoder_buf[1] >> 3) & 0b00011111;
    angle = (float)(rx_encoder_buf[1] | ((rx_encoder_buf[0] & 0b01111111) << 5));
    angle = (angle*360)/4096;
    return angle;
  }
  /*** error data ***/
  else
    return -1;
}
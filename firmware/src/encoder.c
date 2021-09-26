#include <encoder.h>
#include <common.h>

/*============================================================================*/
/* LINE CONFIGURATION                                                         */
/*============================================================================*/

#define MISO_ENCODER PAL_LINE(GPIOA, 6)
#define MOSI_ENCODER PAL_LINE(GPIOA, 7)
#define CLK_ENCODER PAL_LINE(GPIOA, 5)
#define CS_ENCODER PAL_LINE(GPIOB, 6)



static SPIDriver* Encoder = &SPID1;

/*** SPI config ***/
static SPIConfig conf = {
	/*** interrupt off ***/
	.end_cb = NULL,
	/*** CS ***/
	.ssline = CS_ENCODER,
	/***  SPI enable, fclk/256 ***/
	.cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0
};


/**
 * @brief   Initialize periphery connected to encoder
 */
void Encoder_init(void)
{
	spiStart(Encoder, &conf);
	palSetLineMode(CS_ENCODER, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLineMode(CLK_ENCODER, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
	palSetLineMode(MISO_ENCODER, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
	palSetLineMode(MOSI_ENCODER, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);

}

/**
 * @brief recieve data from encoder
 * @return  angle of rotation
 * @return error
 */
float Encoder_RX(void)
{
	uint8_t rx_encoder_buf[3] = {0};
	float angle = 0;

	spiSelect(Encoder);
	spiReceive(Encoder, 3, rx_encoder_buf);
	spiUnselect(Encoder);

	/*** check data ***/
	if((rx_encoder_buf[1]&OCF) && !(rx_encoder_buf[1]&COF) && !(rx_encoder_buf[1]&LIN))
	{
		rx_encoder_buf[1]=(rx_encoder_buf[1] >> 5) & 0b00011111;
		angle = rx_encoder_buf[1] | ((rx_encoder_buf[0] & 0b01111111) << 5);
		angle = (angle*360)/4096;
		return angle;
	}
	/*** error data ***/
	else
		return -1;
}






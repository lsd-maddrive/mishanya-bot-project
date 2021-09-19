#include <encoder.h>
#include <common.h>

/*============================================================================*/
/* LINE CONFIGURATION                                                         */
/*============================================================================*/

#define MISO_SPI1 PAL_LINE(GPIOA, 6)
#define MOSI_SPI1 PAL_LINE(GPIOA, 7)
#define CLK_SPI1 PAL_LINE(GPIOA, 5)
#define CS_SPI1 PAL_LINE(GPIOB, 6)



static SPIDriver* spi1 = &SPID1;

/*** SPI config ***/
static SPIConfig conf = {
	/*** interrupt off ***/
    .end_cb = NULL,
	/*** CS ***/
    .ssline = PAL_LINE(GPIOB, 6),
	/***  SPI enable, fclk/256 ***/
	.cr1 = SPI_CR1_SPE | SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0
};


/**
 * @brief   Initialize periphery connected to encoder
 */
void SPI_init(void)
{
	spiStart(spi1, &conf);
	palSetLineMode(CS_SPI1, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLineMode(CLK_SPI1, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
	palSetLineMode(MISO_SPI1, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
	palSetLineMode(MOSI_SPI1, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);

}

/**
 * @brief recieve data from encoder
 * @return  angle of rotation
 * @return error
 */
int SPI_RX(void)
{
    uint8_t rx_encoder_buf[2] = {0};
    int angle = 0;

	spiSelect(spi1);
	spiReceive(spi1, 3, rx_encoder_buf);
	spiUnselect(spi1);

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






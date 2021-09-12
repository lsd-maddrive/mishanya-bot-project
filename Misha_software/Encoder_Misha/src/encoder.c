#include <encoder.h>
#include <common.h>


#define MISO_SPI1 PAL_LINE(GPIOA, 6)
#define MOSI_SPI1 PAL_LINE(GPIOA, 7)
#define CLK_SPI1 PAL_LINE(GPIOA, 5)
#define CS_SPI1 PAL_LINE(GPIOB, 6)


static SPIDriver* spi1 = &SPID1;

//s Структура конфигурации, circular режим выключен в halconf.h, CS задается как PAL_LINE
static SPIConfig conf = {
    // Не используем прерывания
    .end_cb = NULL,
    // CS вешаем на ногу B6
    .ssline = PAL_LINE(GPIOB, 6),
	// Значение предделителя 16; длина 16 бит; только прием данных
	.cr1 = SPI_CR1_BIDIOE | SPI_CR1_SPE | SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0 //| SPI_CR1_CRCEN | SPI_CR1_CRCNEXT
};



void SPI_init(void)
{
	spiStart(spi1, &conf);
	palSetLineMode(CS_SPI1, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLineMode(CLK_SPI1, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
	palSetLineMode(MISO_SPI1, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
	palSetLineMode(MOSI_SPI1, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);

}

int SPI_RX(void)
{
    uint8_t rx_encoder_buf[2] = {0};
    int angle = 0;
	spiSelect(spi1);
	spiReceive(spi1, 3, rx_encoder_buf);
	spiUnselect(spi1);
	if((rx_encoder_buf[1]&OCF) && !(rx_encoder_buf[1]&COF) && !(rx_encoder_buf[1]&LIN))
	{
		rx_encoder_buf[1]=(rx_encoder_buf[1] >> 5) & 0b00011111;
		angle = rx_encoder_buf[1] | ((rx_encoder_buf[0] & 0b01111111) << 5);
		angle = (angle*360)/4096;
		return angle;
	}
	else
		return -1;
}






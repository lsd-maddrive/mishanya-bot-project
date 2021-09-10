#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#define OCF 0b00000100
#define COF 0b00000010
#define LIN 0b00000001
#define MagINC 0b10000000
#define MagDEC 0b01000000
#define EvenPAR 0b01000000







static const SerialConfig sd_st_cfg = {
  .speed = 115200,
  .cr1 = 0, .cr2 = 0, .cr3 = 0
};

static SerialDriver         *debug_serial = &SD2;
static BaseSequentialStream *debug_stream = NULL;


void debug_stream_init( void )
{
    sdStart( debug_serial, &sd_st_cfg );
	palSetPadMode( GPIOA, 2, PAL_MODE_ALTERNATE(7) );    // TX
	palSetPadMode( GPIOA, 3, PAL_MODE_ALTERNATE(7) );    // RX

    debug_stream = (BaseSequentialStream *)debug_serial;
}

void dbgprintf( const char* format, ... )
{
    if ( !debug_stream )
        return;

    va_list ap;
    va_start(ap, format);
    chvprintf(debug_stream, format, ap);
    va_end(ap);
}



SPIDriver* spi1 = &SPID1;


//s Структура конфигурации, circular режим выключен в halconf.h, CS задается как PAL_LINE
	static SPIConfig conf = {
    // Не используем прерывания
    .end_cb = NULL,
    // CS вешаем на ногу B6
    .ssline = PAL_LINE(GPIOB, 6),
	// Значение предделителя 16; длина 16 бит; только прием данных
	.cr1 = SPI_CR1_BIDIOE | SPI_CR1_SPE | SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0 | SPI_CR1_CRCEN | SPI_CR1_CRCNEXT
};



int main(void) {


    halInit();
    chSysInit();
	debug_stream_init();


    spiStart(spi1, &conf);



    palSetLineMode(PAL_LINE(GPIOB, 6), PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(PAL_LINE(GPIOA, 5), PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(PAL_LINE(GPIOA, 6), PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(PAL_LINE(GPIOA, 7), PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);



    uint8_t rxbuf[2] = {0};
    uint16_t result = 0;
//    uint16_t crc = 0;
    while (1)
    {
    	chThdSleepMilliseconds(100);
		spiSelect(spi1);
		spiReceive(spi1, 3, rxbuf);
		spiUnselect(spi1);
		if((rxbuf[1]&OCF) && !(rxbuf[1]&COF) && !(rxbuf[1]&LIN))
		{
			dbgprintf("check is ok\r\n");
			rxbuf[1]=(rxbuf[1] >> 5) & 0b00011111;
			result = rxbuf[1] | ((rxbuf[0] & 0b01111111) << 5);
//			result = (result*360)/4096;
			dbgprintf("angle=%d\r\n", result);
		}

//		dbgprintf("checksum=%d\r\n", SPI1->TXCRCR);
//		dbgprintf("checksum=%d\r\n", (rxbuf[1]&0b00111111));


    }
}

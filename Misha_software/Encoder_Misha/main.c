#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#define k 0.5





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
	// Значение предделителя 16; длина 16 бит; только прием данных SPI_CR1_DFF
	.cr1 = SPI_CR1_BIDIOE | SPI_CR1_SPE | SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0
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
    while (1)
    {
    	chThdSleepMilliseconds(500);
		spiSelect(spi1);
		spiReceive(spi1, 3, rxbuf);
		spiUnselect(spi1);
		rxbuf[1]=(rxbuf[1] >> 4) & 0b00001111;
		result = rxbuf[1] | (rxbuf[0] << 4);
//		result = (result*360)/4095;
		dbgprintf("angle=%d\r\n", result);

    }
}

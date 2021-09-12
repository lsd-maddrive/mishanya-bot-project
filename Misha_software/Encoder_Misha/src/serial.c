#include <serial.h>
#include <common.h>

#define SerialTX PAL_LINE(GPIOA, 2) // connected via a debug board via usb
#define SerialRX PAL_LINE(GPIOA, 3) // connected via a debug board via usb


static SerialDriver         *debug_serial = &SD2;
static BaseSequentialStream *debug_stream = NULL;

static const SerialConfig sd_st_cfg = {
  .speed = 115200,
  .cr1 = 0, .cr2 = 0, .cr3 = 0
};


void debug_stream_init( void )
{
    sdStart( debug_serial, &sd_st_cfg);
	palSetLineMode(SerialRX,  PAL_MODE_ALTERNATE(7)); // RX
	palSetLineMode(SerialTX,  PAL_MODE_ALTERNATE(7)); // TX

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

#include "test.h"
#include "serial.h"
#include "hal_queues.h"

static const SerialConfig sdcfg = {
        .speed  = 115200,
        .cr1    = 0,
        .cr2    = 0,
        .cr3    = 0
};

void testJoystick(void) {
    debug_stream_init();
    sdStart(&SD4, &sdcfg);
    palSetPadMode(GPIOD, 0, PAL_MODE_ALTERNATE(8));
    palSetPadMode(GPIOD, 1, PAL_MODE_ALTERNATE(8));
    uint8_t buf[12] = {0, 0, 0};
    uint8_t i = 0;
    systime_t time = chVTGetSystemTime();
    while(1) {
        sdReadTimeout( &SD4, (uint8_t*)&buf, 12, TIME_IMMEDIATE );
        i = 0;
        while(i < 12) {
            dbgprintf(" i:%d val: %d",  i, buf[i]);
            ++i;
        }
        dbgprintf("\n\r");

        //dbgprintf("vx%d vy:%d w:%d \n\r",  (int32_t)(buf[1] * 100), (int32_t)(buf[2] * 100), (int32_t)(buf[0] * 100));
        //chprintf( (BaseSequentialStream *)&SD3, "Vx:%d Vy:%d w:%d\n\r", (int32_t)(buf[1] * 100), (int32_t)(buf[2] * 100), (int32_t)(buf[0] * 100));

        time = chThdSleepUntilWindowed( time, time + TIME_MS2I(100));
    }
}
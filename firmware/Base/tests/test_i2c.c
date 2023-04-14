#include "test.h"
#include "i2c.h"
#include "cnfg_peripherals.h"
#include "serial.h"

void testI2C(void) {
    uint8_t rxBuffer[0];

    initI2C();
    debug_stream_init();

    msg_t     msg  = i2cRegisterRead(ADDRESS_GYROSCOPE, REGISTER_WHO_I_AM, rxBuffer, 1, 1000);
    dbgprintf("WHO_I_AM: %d \n\r", rxBuffer[0]);

    if (rxBuffer[0] == WHO_I_AM) {
        palSetLine(LINE_LED1);
    }
    while (1) {
        chThdSleepMilliseconds(1000);
    }
}

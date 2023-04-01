#include "i2c.h"
#include "serial.h"

static bool flagInitI2C = false;

static I2CDriver* i2cDriver = &I2CD1;

static const I2CConfig i2c1Conf = {
        STM32_TIMINGR_PRESC(1U)  |
        STM32_TIMINGR_SCLDEL(9U)  | STM32_TIMINGR_SDADEL(9U) |
        STM32_TIMINGR_SCLH(21U)   | STM32_TIMINGR_SCLL(24U),
        0,                         // CR1
        0                          // CR2
};

void i2cStopDriver(void) {
    i2cStop(i2cDriver);
}


void initI2C(void) {
    i2cStopDriver();
    if(flagInitI2C){
        return;
    }
    palSetLineMode(SCL, PAL_MODE_ALTERNATE(AF_I2C) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP |
                        PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(SDA, PAL_MODE_ALTERNATE(AF_I2C) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP |
    PAL_STM32_OSPEED_HIGHEST);
    i2cStart(i2cDriver, &i2c1Conf);
    flagInitI2C = true;
}

msg_t i2cSimpleWrite(uint8_t address, uint8_t *txbuf, uint8_t length, uint16_t timeout) {
    msg_t msg = i2cMasterTransmitTimeout( i2cDriver, address, txbuf, length, NULL, 0, timeout );
    return msg;
}

msg_t i2cSimpleRead(uint8_t address, uint8_t *rxbuf, uint8_t length, uint16_t timeout) {
    msg_t msg = i2cMasterReceiveTimeout( i2cDriver, address, rxbuf, length, timeout );
    return msg;
}

msg_t i2cRegisterRead(uint8_t address, uint8_t register_addr, uint8_t *rxbuf, uint8_t length, uint16_t timeout) {
    msg_t msg = i2cMasterTransmitTimeout( i2cDriver, address, &register_addr, 1, rxbuf, length, timeout );
    return msg;
}

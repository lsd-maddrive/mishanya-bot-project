#ifndef BASE_I2C_H
#define BASE_I2C_H

#include "common.h"
#include "cnfg_peripherals.h"


void i2cStopDriver(void);

void initI2C(void);

msg_t i2cSimpleWrite(uint8_t address, uint8_t *txbuf, uint8_t length, uint16_t timeout);

msg_t i2cSimpleRead(uint8_t address, uint8_t *rxbuf, uint8_t length, uint16_t timeout);

msg_t i2cRegisterRead(uint8_t address, uint8_t register_addr, uint8_t *rxbuf, uint8_t length, uint16_t timeout);


#endif //BASE_I2C_H

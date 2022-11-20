#ifndef FLASH_F7_H
#define FLASH_F7_H

#include "stdint.h"
#include "stddef.h"
#include "cmsis_gcc.h"
#include "stm32f767xx.h"


typedef enum
{
    FLASH_ERROR_NONE        = 0U,
    FLASH_ERROR             = 1U,
} flash_errors_t;

typedef enum
{
    FLASH_FREE              = 0U,
    FLASH_BUSY              = 1U,
} flash_status_t;


flash_errors_t flash_write_word(uint32_t flash_address, uint32_t data);
flash_errors_t flash_write_block(uint32_t flash_address, void *data, size_t size);
flash_errors_t flash_erase_sector(uint32_t sector);


#endif //FLASH_F7_H

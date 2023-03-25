#include "flash_f7.h"
#include "common.h"

#define FLASH_KEY1                          0x45670123U // datasheet information
#define FLASH_KEY2                          0xCDEF89ABU // datasheet information

static flash_status_t flash_busy_status(void);
static flash_errors_t flash_error_check(void);
static void flash_unlock(void);
static void flash_lock(void);

static void flash_unlock(void)
{
    // flash key
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;

    // enable use flash
    FLASH->CR |= FLASH_CR_PG;
}

static flash_status_t flash_busy_status(void)
{
    if(FLASH->SR & FLASH_SR_BSY)
    {
        return FLASH_BUSY;
    }

    return FLASH_FREE;
}

static void flash_lock(void)
{
    // disable use flash
    FLASH->CR &= (~FLASH_CR_PG);

    // lock flash
    FLASH->CR |= FLASH_CR_LOCK;
}

static flash_errors_t flash_error_check(void)
{
    uint32_t errors = FLASH_SR_WRPERR | FLASH_SR_OPERR | FLASH_SR_PGAERR | FLASH_SR_PGPERR;
    if(FLASH->SR & errors)
    {
        return FLASH_ERROR;
    }
    return FLASH_ERROR_NONE;
}

flash_errors_t flash_write_word(uint32_t flash_address, uint32_t data)
{

    FLASH->SR |= FLASH_SR_EOP | FLASH_SR_PGAERR | FLASH_SR_WRPERR | FLASH_SR_OPERR;

    __disable_irq();

    flash_unlock();

    while(flash_busy_status() == FLASH_BUSY)
    {
        ;
    }

    // write with 4bytes
    FLASH->CR |= FLASH_CR_PSIZE_1;

    while(flash_busy_status() == FLASH_BUSY)
    {
        ;
    }

    *(uint32_t*)flash_address = data;

    __DSB();

    while(flash_busy_status() == FLASH_BUSY)
    {
        ;
    }

    flash_errors_t operation_status = flash_error_check();

    flash_lock();

    __enable_irq();

    return operation_status;
}

flash_errors_t flash_write_block(uint32_t flash_address, void* data, size_t size)
{
    uint32_t address_align = sizeof(uint32_t);
    uint32_t word_to_write = 0;
    size_t amount_bytes_recorded = 0;

    // check address align
    if(flash_address % address_align)
    {
        return FLASH_ERROR;
    }

    while(size != amount_bytes_recorded)
    {
        if(size >= (address_align + amount_bytes_recorded))
        {
            word_to_write = *(uint32_t*)(data+amount_bytes_recorded);
            amount_bytes_recorded += address_align;
        }
        else
        {
            // already recorded qty of bytes
            size_t shift_recorded = amount_bytes_recorded;
            // word = 4 bytes
            size_t shift_inside_word;

            for(;amount_bytes_recorded < (shift_recorded + address_align); amount_bytes_recorded++)
            {
                shift_inside_word = (amount_bytes_recorded - shift_recorded);
                if(amount_bytes_recorded < size)
                {
                    word_to_write |= *(uint32_t*)(data + amount_bytes_recorded) << (8*shift_inside_word);
                }
                else
                {
                    word_to_write |= (uint32_t)0xFF << (8*shift_inside_word);
                }
            }
        }

        if(flash_write_word(flash_address, word_to_write) == FLASH_ERROR)
        {
            return FLASH_ERROR;
        }

        flash_address += address_align;

    }

    return FLASH_ERROR_NONE;
}


flash_errors_t flash_erase_sector(uint32_t sector)
{
    __disable_irq();

    flash_unlock();

    while(flash_busy_status() == FLASH_BUSY)
    {
        ;
    }

    // write with 2bytes
    FLASH->CR |= FLASH_CR_PSIZE_1;

    // enable use flash
    FLASH->CR |= FLASH_CR_PG;

    // choose sector to erase & set bit of erase sector
    FLASH->CR |= FLASH_CR_SER | (sector << FLASH_CR_SNB_Pos);

    // start erase
    FLASH->CR|= FLASH_CR_STRT;

    while(flash_busy_status() == FLASH_BUSY)
    {
        ;
    }

    flash_errors_t operation_status = flash_error_check();

    // reset a bit of erase sector
    FLASH->CR &= ~FLASH_CR_SER;

    flash_lock();

    __enable_irq();

    return operation_status;
}

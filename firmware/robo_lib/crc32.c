#include "crc32.h"


static const uint32_t CRC32_POLY_R = 0xedb88320;
uint32_t crc32_table[256];

void crc32_init(void)
{
    uint32_t i, j;
    uint32_t cr;

    for (i = 0; i < 256; ++i)
    {
        cr = i;
        for (j = 8; j > 0; --j)
        {
            cr = cr & 0x00000001 ? (cr >> 1) ^ CRC32_POLY_R : (cr >> 1);
        }
        crc32_table[i] = cr;
    }
}


uint32_t crc32(uint32_t init_crc, const uint8_t *data, size_t length)
{
    uint32_t v;
    uint32_t crc = ~init_crc;

    while (length > 0)
    {
        v = *data++;
        crc = (crc >> 8) ^ crc32_table[(crc ^ (v)) & 0xff];
        length--;
    }

    return ~crc;
}
//
// Created by Anton on 04.12.2022.
//

#ifndef CRC32_H
#define CRC32_H

#include "stdint.h"
#include "stddef.h"

void crc32_init(void);
uint32_t crc32(uint32_t init_crc, const uint8_t *data, size_t length);

#endif //CRC32_H

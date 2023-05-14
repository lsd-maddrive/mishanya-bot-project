//
// Created by Anton on 28.04.2023.
//

#ifndef TORSE_CAPTURE_H
#define TORSE_CAPTURE_H

#include "common.h"

typedef struct
{
    ioline_t capture_line[ARM_QTY];
}capture_t;

void capture_init(capture_t* capture, ioline_t right_capture, ioline_t left_capture);


#endif //TORSE_CAPTURE_H

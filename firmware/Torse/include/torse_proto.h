#ifndef TORSE_TORSE_PROTO_H
#define TORSE_TORSE_PROTO_H

#include "stdint.h"
#include "stddef.h"
#include "crc32.h"
#include "arm_calibration.h"


typedef enum
{
    TORSE_CALIB = 0,
    TORSE_CALIB_ANGLE_VALUES = 1,
    TORSE_LEFT_ENCODERS_VALUES = 2,
    TORSE_RIGHT_ENCODERS_VALUES = 3,
    TORSE_LEFT_SET_COOR = 4,
    TORSE_RIGHT_SET_COOR = 5,
    TORSE_RIGHT_GRIP_APART = 6,
    TORSE_RIGHT_GRIP_TOGETHER = 7,
    TORSE_LEFT_GRIP_APART = 8,
    TORSE_LEFT_GRIP_TOGETHER = 9,
}torse_proto_gui_cmd_t;


void torse_proto_init(void);
void torse_proto_put_msg(uint8_t* msg, size_t len);

#endif //TORSE_TORSE_PROTO_H

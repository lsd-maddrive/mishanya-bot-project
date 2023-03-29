#ifndef TORSE_TORSE_PROTO_H
#define TORSE_TORSE_PROTO_H

#include "stdint.h"
#include "stddef.h"
#include "crc32.h"
#include "arm_calibration.h"


typedef enum
{
    ARM_PROTO_GUI_CALIB = 0,
    ARM_PROTO_GUI_ANGLE_VALUES = 1,
    ARM_PROTO_GUI_LEFT_ENCODERS_VALUES = 2,
    ARM_PROTO_GUI_RIGHT_ENCODERS_VALUES = 3,
}torse_proto_gui_cmd_t;

typedef enum
{
    NO_ERROR = 0,
    PREFIX_ERROR = 1,
    CRC_ERROR = 2,
    LEN_ERROR = 3,
    WAIT_MSG = 4
}torse_proto_gui_error_t;

#pragma pack(push)
#pragma pack(1)

typedef struct
{
    uint8_t arm_proto_gui_prefix;
    uint8_t msg_len;
    uint8_t msg_cmd;
    uint32_t crc;
    uint8_t msg[255];
}torse_proto_gui_pctk_t;

#pragma pack(pop)

void torse_proto_init(SerialDriver* serial_port);
torse_proto_gui_error_t torse_proto_parser(uint8_t* msg, size_t msg_size);
void torse_proto_send_cmd(torse_proto_gui_cmd_t cmd, uint8_t* data, size_t data_size);
void torse_proto_put_msg(uint8_t* msg, size_t len);

#endif //TORSE_TORSE_PROTO_H

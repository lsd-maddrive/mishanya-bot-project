#ifndef TORSE_ARM_PROTO_GUI_H
#define TORSE_ARM_PROTO_GUI_H

#include "stdint.h"
#include "stddef.h"
#include "crc32.h"
#include "arm_calibration.h"

#define ARM_PROTO_GUI_PREFIX_SIZE     1U
#define ARM_PROTO_GUI_LEN_SIZE        1U
#define ARM_PROTO_GUI_CMD_SIZE        1U
#define ARM_PROTO_GUI_CRC_SIZE        4U
#define ARM_PROTO_GUI_INFO_SIZE       (ARM_PROTO_GUI_PREFIX_SIZE + \
                                        ARM_PROTO_GUI_LEN_SIZE +   \
                                        ARM_PROTO_GUI_CMD_SIZE +   \
                                        ARM_PROTO_GUI_CRC_SIZE)
#define ARM_PROTO_GUI_PREFIX          ((uint8_t)0x52)


typedef enum
{
    ARM_PROTO_GUI_CALIB = 0,
    ARM_PROTO_GUI_ANGLE_VALUES = 1,
    ARM_PROTO_GUI_LEFT_ENCODERS_VALUES = 2,
    ARM_PROTO_GUI_RIGHT_ENCODERS_VALUES = 3,
}arm_proto_gui_cmd_t;

typedef enum
{
    NO_ERROR = 0,
    PREFIX_ERROR = 1,
    CRC_ERROR = 2,
    LEN_ERROR = 3,
    WAIT_MSG = 4
}arm_proto_gui_error_t;

#pragma pack(push)
#pragma pack(1)

typedef struct
{
    uint8_t arm_proto_gui_prefix;
    uint8_t msg_len;
    uint8_t msg_cmd;
    uint32_t crc;
    uint8_t msg[255];
}arm_proto_gui_pctk_t;

#pragma pack(pop)

void arm_proto_gui_init(SerialDriver* serial_port);
arm_proto_gui_error_t arm_proto_gui_parser(uint8_t* msg, size_t msg_size);
void arm_proto_gui_send_cmd(arm_proto_gui_cmd_t cmd, uint8_t* data, size_t data_size);

#endif //TORSE_ARM_PROTO_GUI_H
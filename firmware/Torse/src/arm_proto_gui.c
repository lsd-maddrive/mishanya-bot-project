#include "arm_proto_gui.h"


arm_proto_gui_error_t arm_proto_gui_parser(uint8_t* msg, size_t msg_size)
{
    arm_proto_gui_pctk_t* proto_msg = (void*)msg;

    if(proto_msg->arm_proto_gui_prefix == ARM_PROTO_GUI_PREFIX)
    {
        size_t data_size = msg_size -
                (ARM_PROTO_GUI_PREFIX_SIZE + ARM_PROTO_GUI_CMD_SIZE + ARM_PROTO_GUI_LEN_SIZE + ARM_PROTO_GUI_CRC_SIZE);
        uint32_t crc = crc32(0, (uint8_t*)proto_msg,
                             (ARM_PROTO_GUI_PREFIX_SIZE + ARM_PROTO_GUI_CMD_SIZE + ARM_PROTO_GUI_LEN_SIZE));
        crc = crc32(crc, (uint8_t*)proto_msg->msg, data_size);

        if(crc != proto_msg->crc)
        {
            return CRC_ERROR;
        }

        switch (proto_msg->msg_cmd) {
            case ARM_PROTO_GUI_CALIB:
            {
                arm_calibration_start();
            }
            break;
        }

        return NO_ERROR;
    }

    return PREFIX_ERROR;
}
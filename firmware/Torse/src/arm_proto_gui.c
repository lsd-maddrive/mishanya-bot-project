#include "arm_proto_gui.h"


arm_proto_gui_error_t arm_proto_gui_parser(uint8_t* msg, size_t msg_size)
{
    arm_proto_gui_pctk_t* proto_msg = (void*)msg;

    if(proto_msg->arm_proto_gui_prefix == ARM_PROTO_GUI_PREFIX)
    {
        
    }

    return PREFIX_ERROR;
}
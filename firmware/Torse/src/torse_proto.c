#include "torse_proto.h"
#include "mproto.h"
#include "hal_queues.h"

#define M_BUFFER_SIZE 256
static uint8_t m_proto_buf[M_BUFFER_SIZE];
static mproto_ctx_t m_proto;
static input_queue_t m_queue;

static int16_t read_byte(void)
{
    return (int16_t)iqGetI(&m_queue);
}

static void write_bytes(uint8_t *data, size_t len)
{

}

static mptime_t get_time(void)
{

}


mproto_func_ctx_t funcs_ctx = {
        .get_byte = read_byte,
        .put_bytes = write_bytes,
        .get_time = get_time
};

void torse_proto_init(SerialDriver* serial_port)
{
    mproto_func_ctx_t m_proto_function;
    iqObjectInit(&m_queue, m_proto_buf, M_BUFFER_SIZE, NULL, NULL);


//    m_proto_function.get_byte = serial1_get_byte;
//    m_proto_function.put_bytes = serial1_put_bytes;
//    m_proto_function.get_time = get_time;
//
//    mproto_s1 = mproto_init(&m_proto_function);
}

void torse_proto_put_msg(uint8_t* msg, size_t len)
{
    palToggleLine(LINE_LED1);
    for(size_t i = 0; i < len; i++)
    {
        iqPutI(&m_queue, msg[i]);
    }
}

//static void arm_send_angle_values(void)
//{
//    float arm_values[CALIBRATION_ANGLE_QTY];
//
//    memcpy((uint8_t*)arm_values, (uint32_t*)BASE_CALIBRATION_ADDRESS, sizeof(arm_values));
//
//    arm_proto_gui_send_cmd(ARM_PROTO_GUI_ANGLE_VALUES, (uint8_t*)arm_values, sizeof(arm_values));
//}
//
//static void arm_send_encoders_values(arm_side_t side)
//{
//    float encoder_values[ENCODER_QTY];
//
//    encoder_values[0] = elbow_read_angle(side);
//    encoder_values[1] = v_shoulder_read_angle(side);
//    encoder_values[2] = h_shoulder_read_angle(side);
//
//    arm_proto_gui_cmd_t cmd;
//
//    if(side == LEFT)
//    {
//        cmd = ARM_PROTO_GUI_LEFT_ENCODERS_VALUES;
//    }
//    else if(side == RIGHT)
//    {
//        cmd = ARM_PROTO_GUI_RIGHT_ENCODERS_VALUES;
//    }
//
//    arm_proto_gui_send_cmd(cmd, (uint8_t*)encoder_values, sizeof(encoder_values));
//}
//
//
//void arm_proto_gui_send_cmd(arm_proto_gui_cmd_t cmd, uint8_t* data, size_t data_size)
//{
//  size_t all_msg_size = ARM_PROTO_GUI_INFO_SIZE + data_size;
//
//  proto_buffer.arm_proto_gui_prefix = ARM_PROTO_GUI_PREFIX;
//  proto_buffer.msg_cmd = cmd;
//  proto_buffer.msg_len = data_size;
//  memcpy(proto_buffer.msg, data, data_size);
//  proto_buffer.crc = crc32(0, (uint8_t*)&proto_buffer,
//                              (ARM_PROTO_GUI_PREFIX_SIZE + ARM_PROTO_GUI_CMD_SIZE + ARM_PROTO_GUI_LEN_SIZE));
//  proto_buffer.crc = crc32(proto_buffer.crc, (uint8_t*)proto_buffer.msg, data_size);
//
//  sdWrite(uart_gui, (uint8_t*)&proto_buffer, all_msg_size);
//
//}
//
//
//arm_proto_gui_error_t arm_proto_gui_parser(uint8_t* msg, size_t msg_size)
//{
//    arm_proto_gui_pctk_t* proto_msg = (void*)msg;
//
//    size_t real_msg_len = proto_msg->msg_len + (ARM_PROTO_GUI_PREFIX_SIZE + ARM_PROTO_GUI_CMD_SIZE +
//            ARM_PROTO_GUI_LEN_SIZE + ARM_PROTO_GUI_CRC_SIZE);
//
//    if(msg_size < real_msg_len)
//    {
//        return WAIT_MSG;
//    }
//    else if (msg_size > real_msg_len)
//    {
//        return LEN_ERROR;
//    }
//
//    if(proto_msg->arm_proto_gui_prefix == ARM_PROTO_GUI_PREFIX)
//    {
//        size_t data_size = msg_size -
//                (ARM_PROTO_GUI_PREFIX_SIZE + ARM_PROTO_GUI_CMD_SIZE + ARM_PROTO_GUI_LEN_SIZE + ARM_PROTO_GUI_CRC_SIZE);
//        uint32_t crc = crc32(0, (uint8_t*)proto_msg,
//                             (ARM_PROTO_GUI_PREFIX_SIZE + ARM_PROTO_GUI_CMD_SIZE + ARM_PROTO_GUI_LEN_SIZE));
//        crc = crc32(crc, (uint8_t*)proto_msg->msg, data_size);
//
//        if(crc != proto_msg->crc)
//        {
//            return CRC_ERROR;
//        }
//
//        switch (proto_msg->msg_cmd) {
//            case ARM_PROTO_GUI_CALIB:
//            {
//                arm_calibration_start();
//                arm_send_angle_values();
//            }
//            break;
//            case ARM_PROTO_GUI_ANGLE_VALUES:
//            {
//                arm_send_angle_values();
//            }
//            break;
//            case ARM_PROTO_GUI_LEFT_ENCODERS_VALUES:
//            {
//                arm_send_encoders_values(LEFT);
//            }
//            break;
//            case ARM_PROTO_GUI_RIGHT_ENCODERS_VALUES:
//            {
//                arm_send_encoders_values(RIGHT);
//            }
//            break;
//            default:
//            {
//
//            }
//            break;
//        }
//
//        return NO_ERROR;
//    }
//
//    return PREFIX_ERROR;
//}
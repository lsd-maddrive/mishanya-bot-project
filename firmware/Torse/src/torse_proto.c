#include "torse_proto.h"
#include "mproto.h"
#include "hal_queues.h"
#include "message_handler.h"
#include "arm_calibration.h"
#include "control_system_handler.h"

#define ENCODER_QTY   3U
#define M_BUFFER_SIZE 64
uint8_t m_proto_in_buf[M_BUFFER_SIZE];
mproto_ctx_t m_proto = NULL;
input_queue_t m_in_queue;

static THD_WORKING_AREA(m_proto_task, 256);


static THD_FUNCTION(m_proto_task_update,arg)
{
    (void)arg;
    systime_t time = chVTGetSystemTimeX();
    while (true)
    {
        mproto_spin(m_proto, 0);
        time = chThdSleepUntilWindowed(time, TIME_MS2I(10)+time);
    }
}


static int16_t read_byte(void)
{
    return (int16_t)iqGetI(&m_in_queue);
}

static void write_bytes(uint8_t *data, size_t len)
{
    message_handler_write_msg(MSG_TYPE_TCP, data, len);
}

static mptime_t get_time(void)
{
    return 0;
}

static void torse_proto_get_calibration_angles_values(void)
{
    size_t angle_values_size = sizeof(float)*CALIBRATION_ANGLE_QTY;

    uint8_t data[angle_values_size];

    arm_calibration_get_calibration_angle_values(data, angle_values_size);

    mproto_send_data(m_proto, TORSE_CALIB_ANGLE_VALUES, data, angle_values_size);
}

static void torse_proto_get_left_encoder_angles_values(void)
{
    float angles[ENCODER_QTY];
    angles[0] = elbow_read_angle(LEFT);
    angles[1] = h_shoulder_read_angle(LEFT);
    angles[2] = v_shoulder_read_angle(LEFT);

    size_t encoder_size = sizeof(float)*ENCODER_QTY;

    uint8_t data[encoder_size];

    memcpy((void*)data, (void*)angles, encoder_size);

    mproto_send_data(m_proto, TORSE_LEFT_ENCODERS_VALUES, data, encoder_size);
}

static void torse_proto_get_right_encoder_angles_values(void)
{
    float angles[ENCODER_QTY];
    angles[0] = elbow_read_angle(RIGHT);
    angles[1] = h_shoulder_read_angle(RIGHT);
    angles[2] = v_shoulder_read_angle(RIGHT);

    size_t encoder_size = sizeof(float)*ENCODER_QTY;

    uint8_t data[encoder_size];

    memcpy(data, (uint8_t*)angles, encoder_size);

    mproto_send_data(m_proto, TORSE_RIGHT_ENCODERS_VALUES, data, encoder_size);
}

static void torse_proto_set_left_coor(uint8_t *data, size_t len)
{
    (void)len;
    coord_t* coord = (void*)data;

    coordinates_set_t status = control_system_handler_set_coordinates(LEFT, coord);

    mproto_send_data(m_proto, TORSE_LEFT_SET_COOR, (uint8_t*)&status, sizeof(uint8_t));
}

static void torse_proto_set_right_coor(uint8_t *data, size_t len)
{
    (void)len;
    coord_t* coord = (void*)data;

    coordinates_set_t status = control_system_handler_set_coordinates(RIGHT, coord);

    mproto_send_data(m_proto, TORSE_RIGHT_SET_COOR, (uint8_t*)&status, sizeof(uint8_t));
}

static void torse_proto_parser(mpcmd_t cmd, uint8_t *data, size_t len)
{
    switch (cmd)
    {
        case TORSE_CALIB:
            arm_calibration_start();
            torse_proto_get_calibration_angles_values();
            break;
        case TORSE_CALIB_ANGLE_VALUES:
            torse_proto_get_calibration_angles_values();
            break;
        case TORSE_LEFT_ENCODERS_VALUES:
            torse_proto_get_left_encoder_angles_values();
            break;
        case TORSE_RIGHT_ENCODERS_VALUES:
            torse_proto_get_right_encoder_angles_values();
            break;
        case TORSE_LEFT_SET_COOR:
            torse_proto_set_left_coor(data, len);
            break;
        case TORSE_RIGHT_SET_COOR:
            torse_proto_set_right_coor(data, len);
            break;
        default:
            break;
    }
}


void torse_proto_init(void)
{
    static mproto_func_ctx_t m_proto_function;
    iqObjectInit(&m_in_queue, m_proto_in_buf, M_BUFFER_SIZE, NULL, NULL);

    m_proto_function.get_byte = read_byte;
    m_proto_function.put_bytes = write_bytes;
    m_proto_function.get_time = get_time;

    m_proto = mproto_init(&m_proto_function);

    mproto_register_command( m_proto, TORSE_CALIB, torse_proto_parser);
    mproto_register_command( m_proto, TORSE_CALIB_ANGLE_VALUES, torse_proto_parser);
    mproto_register_command( m_proto, TORSE_LEFT_ENCODERS_VALUES, torse_proto_parser);
    mproto_register_command( m_proto, TORSE_RIGHT_ENCODERS_VALUES, torse_proto_parser);
    mproto_register_command( m_proto, TORSE_LEFT_SET_COOR, torse_proto_parser);
    mproto_register_command( m_proto, TORSE_RIGHT_SET_COOR, torse_proto_parser);


    chThdCreateStatic(m_proto_task, sizeof(m_proto_task), NORMALPRIO+2,
                      m_proto_task_update, NULL);
}

void torse_proto_put_msg(uint8_t* msg, size_t len)
{
    for(size_t i = 0; i < len; i++)
    {
        iqPutI(&m_in_queue, msg[i]);
    }
}

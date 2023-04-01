#include "torse_proto.h"
#include "mproto.h"
#include "hal_queues.h"
#include "message_handler.h"

#define M_BUFFER_SIZE 64
static uint8_t m_proto_in_buf[M_BUFFER_SIZE];
static mproto_ctx_t m_proto = NULL;
static input_queue_t m_in_queue;

static THD_WORKING_AREA(m_proto_task, 256);


static THD_FUNCTION(m_proto_task_update,arg)
{
    (void)arg;
    systime_t time = chVTGetSystemTimeX();
    while (true)
    {
//        mproto_spin(m_proto, 0);
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

static void torse_proto_start_calibration(mpcmd_t cmd, uint8_t *data, size_t len)
{

}

void torse_proto_init(void)
{
    mproto_func_ctx_t m_proto_function;
    iqObjectInit(&m_in_queue, m_proto_in_buf, M_BUFFER_SIZE, NULL, NULL);

    m_proto_function.get_byte = read_byte;
    m_proto_function.put_bytes = write_bytes;
    m_proto_function.get_time = get_time;

    m_proto = mproto_init(&m_proto_function);

    mproto_register_command( m_proto, TORSE_CALIB, torse_proto_start_calibration);


    chThdCreateStatic(m_proto_task, sizeof(m_proto_task), NORMALPRIO,
                      m_proto_task_update, NULL);
}

void torse_proto_put_msg(uint8_t* msg, size_t len)
{
    for(size_t i = 0; i < len; i++)
    {
        iqPutI(&m_in_queue, msg[i]);
    }
}

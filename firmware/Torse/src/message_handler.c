#include "message_handler.h"
#include <lwipthread.h>
#include <lwip/api.h>
#include "torse_proto.h"

#define SOCKETS_NUMBER 3U

static THD_WORKING_AREA(tcp_connection_task, 1024);
static struct netconn *conn, *newconn;

static sockets_t sockets[SOCKETS_NUMBER];

static void netcon_write_data(void* tcp_conn, uint8_t* data, size_t len)
{
    netconn_write((struct netconn *)tcp_conn, data, len, NETCONN_NOCOPY);
}

static void serial_write_data(void* serial, uint8_t* data, size_t len)
{
    sdWrite((SerialDriver *) serial, data, len);
}

static THD_FUNCTION(tcp_task_update,arg) {
    (void)arg;
    volatile err_t err;
    struct netbuf *inbuf = NULL;
    uint8_t *buf = NULL;
    uint16_t buflen;

    conn = netconn_new(NETCONN_TCP);

    netconn_bind(conn, IP_ADDR_ANY, 8000);

    netconn_listen(conn);
    err = netconn_accept(conn, &newconn);
    if (err == ERR_OK)
    {
        sockets[MSG_TYPE_TCP].interface = newconn;
        sockets[MSG_TYPE_TCP].msg = MSG_TYPE_TCP;
        sockets[MSG_TYPE_TCP].write = netcon_write_data;
        systime_t time = chVTGetSystemTimeX();
        while (1)
        {
            err = netconn_recv(newconn, &inbuf);
            if (err == ERR_OK)
            {
                err = netbuf_data(inbuf, (void **) &buf, &buflen);

                if (err == ERR_OK)
                {
                    palToggleLine(LINE_LED1);
                    torse_proto_put_msg(buf, buflen);
                }
            }

            netbuf_delete(inbuf);
            time = chThdSleepUntilWindowed(time, TIME_MS2I(10)+time);
        }
    }
    netconn_delete(conn);

}

void message_handler_write_msg(msg_type_t msg_type, uint8_t* data, size_t len)
{
    if(sockets[msg_type].write != NULL && sockets[msg_type].interface != NULL)
    {
        sockets[msg_type].write(sockets[msg_type].interface, data, len);
    }
}


void message_handler_init(SerialDriver *radio_socket, SerialDriver *debug_socket)
{

    sockets[MSG_TYPE_RADIO].interface = radio_socket;
    sockets[MSG_TYPE_RADIO].msg = MSG_TYPE_RADIO;
    sockets[MSG_TYPE_RADIO].write = serial_write_data;

    sockets[MSG_TYPE_DEBUG].interface = debug_socket;
    sockets[MSG_TYPE_DEBUG].msg = MSG_TYPE_DEBUG;
    sockets[MSG_TYPE_DEBUG].write = serial_write_data;

    chThdCreateStatic(tcp_connection_task,sizeof(tcp_connection_task),NORMALPRIO,
              tcp_task_update, NULL);

}

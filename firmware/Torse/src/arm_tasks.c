#include "arm_tasks.h"
#include <lwipthread.h>
#include <lwip/api.h>
#include "torse_proto.h"

static SerialDriver *uart_gui;
static struct netconn *conn, *newconn;

static THD_WORKING_AREA(control_system_task, 256);
//static THD_WORKING_AREA(serial_task, 512);
static THD_WORKING_AREA(tcp_connection_task, 1024);


static THD_FUNCTION(control_system_task_update,arg) {
    (void) arg;
    systime_t time = chVTGetSystemTimeX();
    while (1) {
        elbow_update_angle(0.1f);
        v_shoulder_update_angle(0.1f);
        h_shoulder_update_angle(0.1f);
        time = chThdSleepUntilWindowed(time, TIME_MS2I(100)+time);
    }
}

//static THD_FUNCTION(serial_task_update,arg) {
//    (void) arg;
//    static uint8_t gui_buffer[255];
//    static size_t msg_offset = 0;
//    systime_t time = chVTGetSystemTimeX();
//    size_t read_size;
//    while (1) {
//        read_size = sdAsynchronousRead(uart_gui, (gui_buffer+msg_offset), sizeof(gui_buffer)-msg_offset);
//
//        if(read_size > 0)
//        {
//            if(gui_buffer[0] == ARM_PROTO_GUI_PREFIX)
//            {
//              if(arm_proto_gui_parser(gui_buffer, (read_size + msg_offset)) == WAIT_MSG)
//              {
//                msg_offset += read_size;
//              }
//              else
//              {
//                msg_offset = 0;
//              }
//            }
//        }
//        time = chThdSleepUntilWindowed(time, TIME_MS2I(20)+time);
//    }
//}


static THD_FUNCTION(tcp_task_update,arg) {
    (void)arg;
    err_t err;

    struct netbuf *inbuf;
    uint8_t *buf;
    uint16_t buflen;

    conn = netconn_new(NETCONN_TCP);
    struct ip4_addr ip;

    ip.addr = low_level_get_tcp_address();

    netconn_bind(conn, &ip, 8000);

    netconn_listen(conn);
    err = netconn_accept(conn, &newconn);
    if (err == ERR_OK)
    {
        while (1)
        {
            palToggleLine(LINE_LED2);
            err = netconn_recv(conn, &inbuf);
            if (err == ERR_OK)
            {
                netbuf_data(inbuf, (void **) &buf, &buflen);

                torse_proto_put_msg(buf, buflen);

                netbuf_delete(inbuf);
            }
        }
    }
    netconn_delete(conn);

}



void arm_tasks_init(SerialDriver* serial_port)
{
    chThdCreateStatic(control_system_task,sizeof(control_system_task),NORMALPRIO + 1,
                      control_system_task_update, NULL);

//    chThdCreateStatic(serial_task,sizeof(serial_task),NORMALPRIO+1,
//                      serial_task_update, NULL);

    chThdCreateStatic(tcp_connection_task,sizeof(tcp_connection_task),NORMALPRIO - 1,
                      tcp_task_update, NULL);


    uart_gui = serial_port;


}


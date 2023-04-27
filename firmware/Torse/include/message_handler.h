#ifndef TORSE_MESSAGE_HANDLER_H
#define TORSE_MESSAGE_HANDLER_H

#include "common.h"

typedef enum
{
    MSG_TYPE_TCP = 0,
    MSG_TYPE_RADIO = 1,
    MSG_TYPE_DEBUG = 2
}msg_type_t;

typedef struct
{
    msg_type_t msg;
    void* interface;
    void (* write) (void* interface, uint8_t* data, size_t len);
}sockets_t;

void message_handler_init(SerialDriver *radio_socket, SerialDriver *debug_socket);
void message_handler_write_msg(msg_type_t msg_type, uint8_t* data, size_t len);

#endif //TORSE_MESSAGE_HANDLER_H

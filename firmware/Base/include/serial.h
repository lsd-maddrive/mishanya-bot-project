#ifndef INCLUDE_SERIAL_H
#define INCLUDE_SERIAL_H

/**
* @brief   Initialize serial port
*/
void debug_stream_init(void);

/**
* @brief    Print
*/
void dbgprintf(const char* format, ...);

#endif

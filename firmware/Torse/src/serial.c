#include <serial.h>
#include <common.h>

/**
* @brief    Print
*/
void dbgprintf(SerialDriver *sdp, const char* format, ... )
{
    if (sdp == NULL)
        return;

    va_list ap;
    va_start(ap, format);
    chvprintf((BaseSequentialStream*)sdp, format, ap);
    va_end(ap);
}

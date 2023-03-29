#ifndef MAD_PROTO_H_
#define MAD_PROTO_H_
/* Old-style (no pragma) protection used for compatibility */

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

/* 
 * Define number of possible units
 * When initialized more than this number - _init() returns NULL
 * Don`t use more than you plan to use
 * Optimization: 
 *      lower -> saves memory
 * Affect:
 *      mproto_init()
 */
#define MADPROTO_CONTEXT_COUNT  1

/* 
 * Define maximum count of command to be registered
 * Value don`t mean that maximum command value is limited by 20
 * Optimization: 
 *      lower -> saves memory
 * Affect:
 *      mproto_register_command()
 */
#define MADPROTO_MAX_COMMANDS   20

/* 
 * Define size of input buffer [bytes]
 * Must be more than maximum data size
 * If you send only 20 bytes - value 20 is enough
 * Optimization:
 *      lower -> saves memory
 * Affect:
 *      mproto_spin()
 */
#define MADPROTO_INPUT_BUFFER   50

/* 
 * Type for definition of time
 * Units are free to be selected by user ->
 *      Used only for _spin()
 */
#define MAX_TIME_VALUE  UINT32_MAX
typedef uint32_t    mptime_t;
/* Available command values: [0; 250] */
/* [251;255] - reserved for future */
typedef uint8_t     mpcmd_t;
typedef void *      mproto_ctx_t;

typedef enum {
    MPROTO_SPIN_NO_DATA = 0,
    MPROTO_SPIN_TIMEOUT = 1
} mproto_spin_result_t;

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mproto_cmd_cb_t)(mpcmd_t cmd, uint8_t *data, size_t len);

typedef struct
{
    /* Each field must be set or undefined behaviour! */
    /* 
     * Function must return data from bus
     * Return: 
     *   -1 if no data, 
     *   [0;255] - byte value if has data 
     */
    int16_t (*get_byte)(void);
    /*
     * Function must put values to bus
     * Args:
     *   data - pointer to data
     *   len - length of data
     */
    void (*put_bytes)(uint8_t *data, size_t len);
    /*
     * Function must return time in free units:
     *   If it returns [seconds] -> _spin() works for max_time [seconds]
     *   If returns [ms] -> _spin() works for max_time [ms]
     * Return:
     *   Time in free units
     */
    mptime_t (*get_time)(void);

} mproto_func_ctx_t;

/*
 * Setup for protocol init
 * Must be called once to get context for bus and register functions
 * Args:
 *      func_ctx - structure with functions pointers
 * Return:
 *      Context for protocol or NULL is error
 * Note:
 *      Call more than MADPROTO_CONTEXT_COUNT - return NULL
 */
mproto_ctx_t mproto_init(mproto_func_ctx_t *func_ctx);

/*
 * Function for *senders* - send data with command
 * Args:
 *      ctx  - protocol context, get it from _init()
 *      cmd  - command value
 *      data - pointer to data
 *      len  - length of data
 */
void mproto_send_data(mproto_ctx_t ctx, mpcmd_t cmd, uint8_t *data, size_t len);

/* 
 * Function for *receivers* - read input bus and call callbacks
 * Args:
 *      ctx - protocol context, get it from _init()
 *      spin_max_time - maximum processing time in mproto_func_ctx_t.get_time() units
 *          0 - no timeout, read until data end
 *          >0 - read up to count time units
 * Return:
 *      MPROTO_SPIN_NO_DATA - data ended
 *      MPROTO_SPIN_TIMEOUT - time for processing exceeded
 * Note:
 *      If MADPROTO_INPUT_BUFFER is too small - function can damage memory or SIGSEGV
 */
mproto_spin_result_t mproto_spin(mproto_ctx_t ctx, mptime_t spin_max_time);

/* 
 * Function for *receivers* - register callback functions to be called when special command receive
 * Args:
 *      ctx - protocol context, get it from _init()
 *      cmd - command value
 *      cb  - function that will ba called when data with such command appears
 * Note:
 *      Register more commands than MADPROTO_MAX_COMMANDS - next functions are not registered
 */
void mproto_register_command(mproto_ctx_t ctx, mpcmd_t cmd, mproto_cmd_cb_t cb);


#ifdef __cplusplus
}
#endif

#endif // MAD_PROTO_H_

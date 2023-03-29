#include <stdbool.h>

#include "mproto.h"

typedef uint8_t crc_t;

typedef enum
{
    M_START_BYTE = 0,
    M_CMD = 1,
    M_DATA_LEN = 2,
    M_HCHK = 3,
    M_DATA = 4,
    M_DCHK = 5

} rcv_mode_t;

typedef struct
{
    uint8_t start_byte;
    uint8_t cmd;
    uint8_t data_len;

} frame_hdr_t;

typedef struct
{
    /* Commands registration */
    mpcmd_t         registered_codes[MADPROTO_MAX_COMMANDS];
    mproto_cmd_cb_t registered_cbs[MADPROTO_MAX_COMMANDS];
    size_t          registered_count;

    mproto_func_ctx_t   *func_ctx;

    rcv_mode_t      cur_mode;

    uint8_t         rcv_buffer[MADPROTO_INPUT_BUFFER];
    size_t          rcv_bytes;

    uint8_t         crc_buffer[sizeof(crc_t)];
    size_t          crc_bytes;

    frame_hdr_t     hdr;

} internal_ctx_t;

#define START_BYTE  0xe7
#define STOP_BYTE   0x7e

// uint32_t calc_crc32(uint8_t *data, size_t len)
// {
//     return 0x44444422;
// }

/**
 * @brief ROS-like CRC function computation
 *  Compute checksum based on contents sum
 * 
 * @param data Data pointer to computer based on
 * @param len Length of data
 * @return crc_t Result checksum byte
 */
crc_t calc_crc(uint8_t *data, size_t len)
{
    crc_t full_sum = 0;
    for ( size_t i = 0; i < len; i++ ) {
        full_sum += data[i];
    }

    return 255 - full_sum;
}

internal_ctx_t  base_ctx[MADPROTO_CONTEXT_COUNT];
size_t          ctx_last_idx = 0;

/**
 * @brief Execute registered callbacks based on command codes
 * 
 * @param inctx Internal context
 */
static void call_cb_on(internal_ctx_t *inctx)
{
    size_t i;    
    for ( i = 0; i < inctx->registered_count; i++ ) {
        if ( inctx->hdr.cmd == inctx->registered_codes[i] ) {
            inctx->registered_cbs[i](inctx->hdr.cmd, inctx->rcv_buffer, inctx->rcv_bytes);
            break;
        }
    }
}

mproto_ctx_t mproto_init(mproto_func_ctx_t *func_ctx)
{
    if ( ctx_last_idx >= MADPROTO_CONTEXT_COUNT )
        return NULL;

    internal_ctx_t *new_ctx = &base_ctx[ctx_last_idx++];

    new_ctx->func_ctx = func_ctx;
    new_ctx->registered_count = 0;
    new_ctx->rcv_bytes = 0;
    new_ctx->crc_bytes = 0;

    new_ctx->hdr.start_byte = START_BYTE;

    size_t i;
    for ( i = 0; i < MADPROTO_MAX_COMMANDS; i++ )
    {
        new_ctx->registered_cbs[i] = NULL;
    }

    return new_ctx;
}

void mproto_register_command(mproto_ctx_t ctx, mpcmd_t cmd, mproto_cmd_cb_t cb)
{
    internal_ctx_t *inctx = ctx;

    size_t i;
    for ( i = 0; i < inctx->registered_count; i++ )
    {
        if ( cmd == inctx->registered_codes[i] ) {
            inctx->registered_cbs[i] = cb;
            return;
        }
    }

    if ( inctx->registered_count >= MADPROTO_MAX_COMMANDS ) {
        return;
    }

    inctx->registered_cbs[inctx->registered_count] = cb;
    inctx->registered_codes[inctx->registered_count] = cmd;
    inctx->registered_count++;
}

void mproto_send_data(mproto_ctx_t ctx, mpcmd_t cmd, uint8_t *data, size_t len)
{
    internal_ctx_t *inctx = ctx;

    frame_hdr_t hdr;
    hdr.start_byte = START_BYTE;
    hdr.cmd = cmd;
    hdr.data_len = len;

    crc_t hcrc = calc_crc((uint8_t *)&hdr, sizeof(hdr));
    crc_t dcrc = calc_crc(data, len);

    inctx->func_ctx->put_bytes((uint8_t *)&hdr, sizeof(hdr));
    inctx->func_ctx->put_bytes((uint8_t *)&hcrc, sizeof(hcrc));
    if ( data && len > 0 )
        inctx->func_ctx->put_bytes(data, len);
    inctx->func_ctx->put_bytes((uint8_t *)&dcrc, sizeof(dcrc));
}

mproto_spin_result_t mproto_spin(mproto_ctx_t ctx, mptime_t spin_max_time)
{
    internal_ctx_t *inctx = ctx;

    mptime_t startTime = inctx->func_ctx->get_time();

    while ( true )
    {
        if ( spin_max_time > 0 )
        {
            mptime_t curTime = inctx->func_ctx->get_time();
            mptime_t diffTime;

            if ( curTime < startTime ) {
                diffTime = (UINT32_MAX - startTime) + curTime;
            } else {
                diffTime = curTime - startTime;
            }

            if ( diffTime > spin_max_time )
                return MPROTO_SPIN_TIMEOUT;
        }

        int16_t rcv_input = inctx->func_ctx->get_byte();
        if ( rcv_input < 0 )
            return MPROTO_SPIN_NO_DATA;
        
        uint8_t rcv_byte = rcv_input;

        switch (inctx->cur_mode)
        {
            /**
             * Start byte processing, just check that we have required byte
             */
            case M_START_BYTE:
            {
                if ( rcv_byte == START_BYTE )
                    inctx->cur_mode++;
                break;
            }

            /**
             * Get next byte as command to process
             */
            case M_CMD:
            {
                inctx->hdr.cmd = rcv_byte;
                inctx->cur_mode++;
                break;
            }
            
            /**
             * Obtain data length to know how much to read
             */
            case M_DATA_LEN:
            {
                inctx->hdr.data_len = rcv_byte;
                inctx->cur_mode++;
                inctx->crc_bytes = 0;
                break;
            }

            /**
             * Header checksum computation and comparison with sent data
             */
            case M_HCHK:
            {
                inctx->crc_buffer[inctx->crc_bytes++] = rcv_byte;
                
                if ( inctx->crc_bytes == sizeof(crc_t) ) {
                    crc_t *snd_crc = (crc_t *)inctx->crc_buffer;
                    crc_t clc_crc = calc_crc((uint8_t *)&(inctx->hdr), sizeof(inctx->hdr));

                    if ( clc_crc == *snd_crc ) {
                        inctx->cur_mode++;
                        /* Skip data step - cmd only */
                        if ( inctx->hdr.data_len == 0 )
                            inctx->cur_mode++;
                    } else {
                        inctx->cur_mode = M_START_BYTE;
                    }

                    inctx->crc_bytes = 0;
                }
                break;
            }
            
            /**
             * Data receive based on length
             */
            case M_DATA:
            {
                inctx->rcv_buffer[inctx->rcv_bytes++] = rcv_byte;

                if ( inctx->rcv_bytes == inctx->hdr.data_len ) {
                    inctx->cur_mode++;
                    inctx->crc_bytes = 0;
                }
                break;
            }

            /**
             * Data checksum to ensure that data is not corrupted
             */
            case M_DCHK:
            {
                /* Check and call callback */
                inctx->crc_buffer[inctx->crc_bytes++] = rcv_byte;

                if ( inctx->crc_bytes == sizeof(crc_t) ) {
                    crc_t *snd_crc = (crc_t *)inctx->crc_buffer;
                    crc_t clc_crc = calc_crc(inctx->rcv_buffer, inctx->rcv_bytes);

                    if ( clc_crc == *snd_crc ) {
                        call_cb_on(inctx);
                    }

                    // Back to processing start
                    inctx->cur_mode = M_START_BYTE;
                    inctx->rcv_bytes = 0;
                    inctx->crc_bytes = 0;
                }
                break;
            }
        }
    }
}

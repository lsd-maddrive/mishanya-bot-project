#ifndef INCLUDE_ARM_ENCODER_H
#define INCLUDE_ARM_ENCODER_H

#include <common.h>

typedef struct {
    ioline_t          cs_encoder;
    ioline_t          clk_encoder;
    ioline_t          miso_encoder;
}arm_encoder_line_t;

typedef struct
{
    SPIDriver* encoder_ptr;
    SPIConfig encoder_conf;
    arm_encoder_line_t encoder_pins;
}arm_encoder_t;

/**
 * @brief   Initialize periphery connected to encoder
 */
void encoder_init(arm_encoder_t* encoder);

/**
 * @brief recieve data from encoder
 * @return  angle of rotation
 * @return error
 */
float encoder_read(arm_encoder_t* encoder);

#endif

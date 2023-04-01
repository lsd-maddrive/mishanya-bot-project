#ifndef INCLUDE_ENCODER_BASE
#define INCLUDE_ENCODER_BASE

#include <common.h>
#include "cnfg_peripherals.h"

typedef enum {ENCODER_1, ENCODER_2, ENCODER_3} type_encoder;

/**
 * @brief structure for encoder in base
 * @identifier1 port and pin for phase A
 * @identifier2 port and pin for phase B
 * @identifier3 tic_count is number of encoder tics
 * @identifier4 rev_count is number of revolution passed by the encoder
 * @identifier5 direction of rotation of the encoder
 */
typedef struct
{
    ioline_t line_phase_A;
    ioline_t line_phase_B;
    int16_t  tic_count;
    float    rev_count;
    bool     direction_rotation;
}encoder_t;

/**
 * @brief Initialization Interruption
 * @args encoder_n is value from enum
 */
void lldEncoderInit(type_encoder encoder_n);
/**
 * @brief the function counts ticks revolutions and determines the direction
 * @args enc_t is pointer to struct
 */
void ProcessEncoderData(encoder_t* enc_t);

/**
 * @brief Get number of encoder tics
 * @note maximum tics - number of tics one per revolution
 * @args encoder_n is value from enum
 * @return tics passed by the encoder
 */
int16_t GetEncoderRawTicks(type_encoder encoder_n);

/**
 * @brief Get direction of rotation of the encoder
 * @args encoder_n is value from enum
 * @return direction of rotation
 */
bool GetEncoderDirection(type_encoder encoder_n);

/**
 * @brief Get number of revolution passed by the encoder
 * @args encoder_n is value from enum
 * @return number of revolutions + number tics
 */
float GetEncoderRawRevs(type_encoder encoder_n);

/**
 * @brief Reset the value of variables
 * @note variables: number of tics, direction rotation, number of revolution
 */
void ResetEncoder(type_encoder encoder_n);

/**
 * @brief Counts the number of revolutions
 * @args cur_encoder is pointer to the structure
 * @return number of revolutions + number tics
 */
float getRevs(encoder_t* cur_encoder);

#endif

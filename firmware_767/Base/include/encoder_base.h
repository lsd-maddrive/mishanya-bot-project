#ifndef INCLUDE_ENCODER_BASE
#define INCLUDE_ENCODER_BASE

#include <common.h>

typedef enum {ENCODER_1, ENCODER_2, ENCODER_3}type_encoder;

/**
 * @brief structure for encoder in base
 * @identifier1 port and pin for phase A
 * @identifier2 port and pin for phase B
 */
typedef struct
{
    ioline_t line_phase_A;
    ioline_t line_phase_B;
}phase_pin;

/**
 * @brief Initialization Interruption
 * @note variable init_enc for protection
 */
void lldEncoderInit(void);

/**
 * @brief Get number of encoder tics
 * @note maximum tics - number of tics one per revolution
 * @return tics passed by the encoder
 */
int16_t GetEncoderRawTicks(void);

/**
 * @brief Get direction of rotation of the encoder
 * @return direction of rotation
 */
bool GetEncoderDirection(void);

/**
 * @brief Get number of revolution passed by the encoder
 * @return number of revolutions + number tics
 */
float GetEncoderRawRevs(void);

/**
 * @brief Reset the value of variables
 * @note variables: number of tics, direction rotation, number of revolution
 */
void ResetEncoder(void);

/**
 * @brief Gets the encoder type
 * @args encoder is value from enum
 */
void GetTypeEncoder(int8_t encoder);

#endif

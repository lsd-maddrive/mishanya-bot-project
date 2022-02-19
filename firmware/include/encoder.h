#ifndef INCLUDE_ENCODER_H
#define INCLUDE_ENCODER_H



/************ Status bita ************/

#define OCF 0b00000100
#define COF 0b00000010
#define LIN 0b00000001
#define MagINC 0b10000000
#define MagDEC 0b01000000
#define EvenPAR 0b01000000

/************ Status bita ************/


/**
 * @brief   Initialize periphery connected to encoder
 */
void Encoder_init(void);

/**
 * @brief recieve data from encoder
 * @return  angle of rotation
 * @return error
 */
float Encoder_Read(void);

#endif

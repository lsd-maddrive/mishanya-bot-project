#ifndef INCLUDE_ENCODER_H
#define INCLUDE_ENCODER_H

#define OCF 0b00000100     //{
#define COF 0b00000010     //
#define LIN 0b00000001     //
#define MagINC 0b10000000  //   status bits
#define MagDEC 0b01000000  //
#define EvenPAR 0b01000000 //}


void SPI_init(void);

int SPI_RX(void);

#endif

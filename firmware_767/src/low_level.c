////
//// Created by Anton on 09.09.2022.
////
#include "low_level.h"


static void init_gpio();

//// *******************arm spi config******************* //
//
//const arm_encoder_t right_shoulder_in_encoder =
//        {
//                .encoder_ptr = &SPID2,
//                .encoder_pins = {
//                        .cs_encoder = CS_RIGHT_ENCODER_SHOULDER_IN,
//                        .clk_encoder = CLK_ENCODER_RIGHT,
//                        .miso_encoder = MISO_ENCODER_RIGHT
//                },
//                .encoder_conf = {
//                        .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
//                        .end_cb = NULL
//                }
//        };
//
//const arm_encoder_t right_shoulder_out_encoder =
//        {
//                .encoder_ptr = &SPID2,
//                .encoder_pins = {
//                        .cs_encoder = CS_RIGHT_ENCODER_SHOULDER_OUT,
//                        .clk_encoder = CLK_ENCODER_RIGHT,
//                        .miso_encoder = MISO_ENCODER_RIGHT
//                },
//                .encoder_conf = {
//                        .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
//                        .end_cb = NULL
//                }
//        };
//
//const arm_encoder_t left_shoulder_in_encoder =
//        {
//                .encoder_ptr = &SPID1,
//                .encoder_pins = {
//                        .cs_encoder = CS_LEFT_ENCODER_SHOULDER_IN,
//                        .clk_encoder = CLK_ENCODER_LEFT,
//                        .miso_encoder = MISO_ENCODER_LEFT
//                },
//                .encoder_conf = {
//                        .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
//                        .end_cb = NULL
//                }
//        };
//
//const arm_encoder_t left_shoulder_out_encoder =
//        {
//                .encoder_ptr = &SPID1,
//                .encoder_pins = {
//                        .cs_encoder = CS_LEFT_ENCODER_SHOULDER_OUT,
//                        .clk_encoder = CLK_ENCODER_LEFT,
//                        .miso_encoder = MISO_ENCODER_LEFT
//                },
//                .encoder_conf = {
//                        .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
//                        .end_cb = NULL
//                }
//        };
//
//// *******************arm spi config******************* //
//
//// *******************arm spi config******************* //
//PWMDriver * const pwm1Driver = &PWMD1;
//
//const PWMConfig pwm1config = {
//        .frequency = PWM_frequency,
//        .period    = PWM_period,
//        .callback  = NULL,
//        .channels  = {
//                {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // E8  - LEFT_PWM_SHOULDER_IN
//                {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // E11 - LEFT_PWM_SHOULDER_OUT
//                {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // E13 - LEFT_PWM_ELBOW
//                {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
//        },
//        .cr2        = 0,
//        .dier       = 0
//};
//
//PWMDriver * const pwm8Driver = &PWMD8;
//
//const PWMConfig pwm8config = {
//        .frequency = PWM_frequency,
//        .period    = PWM_period,
//        .callback  = NULL,
//        .channels  = {
//                {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// C6 - RIGHT_PWM_SHOULDER_IN
//                {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// C7 - RIGHT_PWM_SHOULDER_OUT
//                {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
//                {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}	// C9 - RIGHT_PWM_ELBOW
//        },
//        .cr2        = 0,
//        .dier       = 0
//};
//// *******************arm spi config******************* //
//
//
void init_low_level()
{
	init_gpio();
}

static void init_gpio()
{
	palSetLineMode(LEFT_UP_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);



}

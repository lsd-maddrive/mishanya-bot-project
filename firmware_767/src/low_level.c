////
//// Created by Anton on 09.09.2022.
////
#include "low_level.h"

#define PWM_frequency		500000
#define PWM_period			10000

static void init_gpio(void);
static void init_pwm(void);
static void init_spi(void);

// *******************arm spi config******************* //

const SPIConfig spi1_conf = {
  .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
  .end_cb = NULL
};

const SPIConfig spi2_conf = {
        .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
        .end_cb = NULL
};

// *******************arm spi config******************* //

// *******************arm pwm config******************* //

const PWMConfig pwm1_config = {
  .frequency = PWM_frequency,
  .period    = PWM_period,
  .callback  = NULL,
  .channels  = {
    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // E8  - LEFT_PWM_SHOULDER_IN
    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // E11 - LEFT_PWM_SHOULDER_OUT
    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // E13 - LEFT_PWM_ELBOW
    {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
  },
  .cr2        = 0,
  .dier       = 0
};

const PWMConfig pwm8_config = {
  .frequency = PWM_frequency,
  .period    = PWM_period,
  .callback  = NULL,
  .channels  = {
    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// C6 - RIGHT_PWM_SHOULDER_IN
    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// C7 - RIGHT_PWM_SHOULDER_OUT
    {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}	// C9 - RIGHT_PWM_ELBOW
  },
  .cr2        = 0,
  .dier       = 0
};
// *******************arm pwm config******************* //

void init_low_level(void)
{
	init_gpio();
  init_pwm();
  init_spi();
}

static void init_gpio(void)
{
	palSetLineMode(LEFT_UP_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LEFT_DOWN_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);

  palSetLineMode(CS_LEFT_ENCODER_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);
  palWriteLine(CS_LEFT_ENCODER_ELBOW, PAL_HIGH);

  palSetLineMode(RIGHT_UP_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(RIGHT_DOWN_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);

  palSetLineMode(CS_RIGHT_ENCODER_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);
  palWriteLine(CS_RIGHT_ENCODER_ELBOW, PAL_HIGH);
}

static void init_pwm(void)
{
  palSetLineMode(LEFT_PWM_ELBOW, PAL_MODE_ALTERNATE(LEFT_ELBOW_ALT_FUNC_NUM));
  pwmStart(&PWMD1, &pwm1_config);

  palSetLineMode(RIGHT_PWM_ELBOW, PAL_MODE_ALTERNATE(RIGHT_ELBOW_ALT_FUNC_NUM));
  pwmStart(&PWMD8, &pwm8_config);
}

static void init_spi(void)
{
  palSetLineMode(CLK_ENCODER_LEFT, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
  palSetLineMode(MISO_ENCODER_LEFT, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
  spiStart(&SPID1, &spi1_conf);

  palSetLineMode(CLK_ENCODER_RIGHT, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
  palSetLineMode(MISO_ENCODER_RIGHT, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
  spiStart(&SPID2, &spi2_conf);
}
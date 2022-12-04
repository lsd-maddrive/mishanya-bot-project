#include "low_level.h"
#include "arms.h"

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
    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // E8  - LEFT HORIZONTAL SHOULDER
    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // E11 - LEFT VERTICAL SHOULDER
    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // E13 - LEFT ELBOW
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
    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// C6 - RIGHT HORIZONTAL SHOULDER
    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// C7 - RIGHT VERTICAL SHOULDER
    {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
    {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}	// C9 - RIGHT ELBOW
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
    arms_init();
}

static void init_gpio(void)
{
  // elbow gpio
	palSetLineMode(LEFT_UP_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LEFT_DOWN_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);

  palSetLineMode(CS_LEFT_ENCODER_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);
  palWriteLine(CS_LEFT_ENCODER_ELBOW, PAL_HIGH);

  palSetLineMode(RIGHT_UP_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(RIGHT_DOWN_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);

  palSetLineMode(CS_RIGHT_ENCODER_ELBOW, PAL_MODE_OUTPUT_PUSHPULL);
  palWriteLine(CS_RIGHT_ENCODER_ELBOW, PAL_HIGH);

  // vertical shoulder gpio
  palSetLineMode(LEFT_UP_V_SHOULDER, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LEFT_DOWN_V_SHOULDER, PAL_MODE_OUTPUT_PUSHPULL);

  palSetLineMode(CS_LEFT_ENCODER_V_SHOULDER, PAL_MODE_OUTPUT_PUSHPULL);
  palWriteLine(CS_LEFT_ENCODER_V_SHOULDER, PAL_HIGH);

  palSetLineMode(RIGHT_UP_V_SHOULDER, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(RIGHT_DOWN_V_SHOULDER, PAL_MODE_OUTPUT_PUSHPULL);

  palSetLineMode(CS_RIGHT_ENCODER_V_SHOULDER, PAL_MODE_OUTPUT_PUSHPULL);
  palWriteLine(CS_RIGHT_ENCODER_V_SHOULDER, PAL_HIGH);

  // horizontal shoulder gpio
  palSetLineMode(LEFT_UP_H_SHOULDER, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LEFT_DOWN_H_SHOULDER, PAL_MODE_OUTPUT_PUSHPULL);

  palSetLineMode(CS_LEFT_ENCODER_H_SHOULDER, PAL_MODE_OUTPUT_PUSHPULL);
  palWriteLine(CS_LEFT_ENCODER_H_SHOULDER, PAL_HIGH);

  palSetLineMode(RIGHT_UP_H_SHOULDER, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(RIGHT_DOWN_H_SHOULDER, PAL_MODE_OUTPUT_PUSHPULL);

  palSetLineMode(CS_RIGHT_ENCODER_H_SHOULDER, PAL_MODE_OUTPUT_PUSHPULL);
  palWriteLine(CS_RIGHT_ENCODER_H_SHOULDER, PAL_HIGH);
}

static void init_pwm(void)
{
  // elbow PWM
  palSetLineMode(LEFT_PWM_ELBOW, PAL_MODE_ALTERNATE(LEFT_PWM_ALT_FUNC_NUM));
  palSetLineMode(RIGHT_PWM_ELBOW, PAL_MODE_ALTERNATE(RIGHT_PWM_ALT_FUNC_NUM));

  // vertical shoulder PWM
  palSetLineMode(LEFT_PWM_V_SHOULDER, PAL_MODE_ALTERNATE(LEFT_PWM_ALT_FUNC_NUM));
  palSetLineMode(RIGHT_PWM_V_SHOULDER, PAL_MODE_ALTERNATE(RIGHT_PWM_ALT_FUNC_NUM));

  // horizontal shoulder PWM
  palSetLineMode(LEFT_PWM_H_SHOULDER, PAL_MODE_ALTERNATE(LEFT_PWM_ALT_FUNC_NUM));
  palSetLineMode(RIGHT_PWM_H_SHOULDER, PAL_MODE_ALTERNATE(RIGHT_PWM_ALT_FUNC_NUM));

  pwmStart(&PWMD1, &pwm1_config);
  pwmStart(&PWMD8, &pwm8_config);
}

static void init_spi(void)
{
  palSetLineMode(CLK_ENCODER_LEFT, PAL_MODE_ALTERNATE(SPI_ALT_FUNC_NUM) | PAL_STM32_OSPEED_HIGHEST);
  palSetLineMode(MISO_ENCODER_LEFT, PAL_MODE_ALTERNATE(SPI_ALT_FUNC_NUM) | PAL_STM32_OSPEED_HIGHEST);


  palSetLineMode(CLK_ENCODER_RIGHT, PAL_MODE_ALTERNATE(SPI_ALT_FUNC_NUM) | PAL_STM32_OSPEED_HIGHEST);
  palSetLineMode(MISO_ENCODER_RIGHT, PAL_MODE_ALTERNATE(SPI_ALT_FUNC_NUM) | PAL_STM32_OSPEED_HIGHEST);

  spiStart(&SPID1, &spi1_conf);
  spiStart(&SPID2, &spi2_conf);
}
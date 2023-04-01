#include "low_level.h"
#include "arms.h"
#include "crc32.h"
#include "arm_calibration.h"
#include "torse_proto.h"
#include "message_handler.h"
#include "control_system_handler.h"

#include <lwipthread.h>

// А это уже сам lwip. Там много всего есть, но я мало что понимаю
#include <lwip/netif.h>
#include <lwip/api.h>

#define PWM_frequency		500000U
#define PWM_period			10000U

static void init_gpio(void);
static void init_pwm(void);
static void init_spi(void);
static void uart_gui_init(void);
static void uart_serial_init(void);
static void tcp_init(void);


static lwipthread_opts_t opts;
// *******************serial uart config******************* //

static const SerialConfig uart_serial_cnfg = {
        .speed = 115200U,
        .cr1 = 0, .cr2 = 0, .cr3 = 0
};

// *******************serial uart config******************* //

// *******************serial uart config******************* //

static const SerialConfig uart_radio_cnfg = {
        .speed = 57600U,
        .cr1 = 0, .cr2 = 0, .cr3 = 0
};

// *******************serial uart config******************* //

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
    crc32_init();
    uart_gui_init();
    uart_serial_init();
    tcp_init();

    control_system_handler_init();
    message_handler_init(&SD2, &SD3);
    calibration_init();
    torse_proto_init();

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

  // info led
  palSetLineMode(LINE_LED2, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_LED1, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_LED3, PAL_MODE_OUTPUT_PUSHPULL);


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


static void uart_gui_init(void)
{
  palSetLineMode(RADIO_RX,  PAL_MODE_ALTERNATE(7));
  palSetLineMode(RADIO_TX,  PAL_MODE_ALTERNATE(7));
  sdStart( &SD2, &uart_radio_cnfg);
}

static void uart_serial_init(void)
{
  palSetLineMode(SERIAL_RX,  PAL_MODE_ALTERNATE(7));
  palSetLineMode(SERIAL_TX,  PAL_MODE_ALTERNATE(7));
  sdStart( &SD3, &uart_serial_cnfg);
}

static void tcp_init(void)
{
    struct ip4_addr ip, gateway, netmask;
    IP4_ADDR(&ip, 172, 18, 193, 10);
    IP4_ADDR(&gateway, 172, 18, 193, 200);
    IP4_ADDR(&netmask, 255, 255, 255, 0);

    uint8_t macaddr[6] = {0xC2, 0xAF, 0x51, 0x03, 0xCF, 0x46};

    opts.address = ip.addr;
    opts.gateway = gateway.addr;
    opts.netmask = netmask.addr;
    opts.macaddress = macaddr;
    opts.link_up_cb = NULL;
    opts.link_down_cb = NULL;

    lwipInit(&opts);
    chThdSleepSeconds(2);
}

uint32_t low_level_get_tcp_address(void)
{
    return opts.address;
}
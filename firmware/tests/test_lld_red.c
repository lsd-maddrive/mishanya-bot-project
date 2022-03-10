#include "test.h"
#include "lld_red_driver.h"
#include "lld_bridge_system.h"
#include "serial.h"

#define PWM_frequency		500000
#define PWM_period			10000


#define DIRECT		PAL_LINE(GPIOB,5)
#define REVERSE	  PAL_LINE(GPIOB,3)
#define PWM		    PAL_LINE(GPIOC,7) // TIM3 CH2

const pwm_channel_t ch_pwm_red = {
  .alt_func_1 = 2,
  .ch_pwm_1 = 1
};

const pwm_ctx_t pwm_ctx_red = {
  .pwm_ch = ch_pwm_red,
  .driver_ptr = &PWMD3,
  .pwm_conf = {
    .frequency = PWM_frequency,
    .period    = PWM_period,
    .callback  = NULL,
    .channels  = {

  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},

  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},

  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},

  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}

    },
    .cr2        = 0,
    .dier       = 0
  }
};

const line_driver_t pin_line_red = {
  .PWM_1 = PWM,
  .digit_2 = REVERSE,
  .digit_1 = DIRECT
};

const control_driver_t test_control_red = {
  .pwm_setting_ctx = pwm_ctx_red,
  .line_control = pin_line_red
};

void test_lld_red(void)
{

  char rcv_data;
  uint8_t test = 0;
  int16_t period = 0;
  debug_stream_init();
  lld_red_init_driver(&pin_line_red, &pwm_ctx_red);

  test = 0;

  while (!test) {
    if (period > 0)
      lld_red_driver_direct(&test_control_red, &ch_pwm_red, period);
    else if (period < 0)
      lld_red_driver_reverse(&test_control_red, &ch_pwm_red, period);
    else
      lld_red_driver_off(&test_control_red, &ch_pwm_red);

    dbgprintf("--------------------\r\n");
    dbgprintf("PWM period(z: +500, x: -500):\r\n");
    rcv_data = sdGet(&SD2);
    switch (rcv_data) {
      case 'z':
        period += 500;
        if (period > 10000)
          period = 10000;
        break;

      case 'x':
        period -= 500;
        if (period < -10000)
          period = -10000;
        break;

      case 'b':
        test = 1;
        lld_red_driver_off(&test_control_red, &ch_pwm_red);
        period = 0;
        break;

      default:
        break;
    }
    dbgprintf("PWM period=%d\r\n", period);
    dbgprintf("--------------------\r\n");
    dbgprintf("\r\n");


  }
}



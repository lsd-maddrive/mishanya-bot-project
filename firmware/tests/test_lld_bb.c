#include "test.h"
#include "lld_bb_driver.h"
#include "lld_bridge_system.h"
#include "serial.h"

#define PWM_frequency		500000
#define PWM_period			10000


#define DIRECT		  PAL_LINE(GPIOB,5)
#define REVERSE	    PAL_LINE(GPIOB,3)
#define PWM1	      PAL_LINE(GPIOA,9) // TIM1 CH2
#define PWM2	      PAL_LINE(GPIOB,0) // TIM1 CH2N

const pwm_channel_t ch_pwm_bb = {
  .ch_pwm_1 = 1,
  .ch_pwm_2 = 1,
  .alt_func_1 = 1,
  .alt_func_2 = 1
};

const pwm_ctx_t pwm_ctx_bb = {
  .pwm_ch = ch_pwm_bb,
  .driver_ptr = &PWMD1,
  .pwm_conf = {
    .frequency = PWM_frequency,
    .period    = PWM_period,
    .callback  = NULL,
    .channels  = {

      {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// LEFT_PWM

      {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// RIGHT_PWM

      {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},

      {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}

    },
    .cr2        = 0,

    // !!!!!!!! THE CALCULATION WAS MADE FOR A CLOCK FREQUENCY OF 8 MHz AND THE APB1 BUS !!!!!!!! //
    .bdtr 		= 0b10011100,
    // !!!!!!!! THE CALCULATION WAS MADE FOR A CLOCK FREQUENCY OF 8 MHz AND THE APB1 BUS !!!!!!!! //

    .dier       = 0
  }
};

const line_driver_t pin_line_bb = {
  .PWM_1 = PWM1,
  .PWM_2 = PWM2,
  .digit_1 = DIRECT,
  .digit_2 = REVERSE
};

const control_driver_t test_control_bb = {
  .pwm_setting_ctx = pwm_ctx_bb,
  .line_control = pin_line_bb
};

void test_lld_bb(void)
{

  char rcv_data;
  uint8_t test = 0;
  int16_t period = 0;
  debug_stream_init();
  lld_bb_init_driver(&pin_line_bb, &pwm_ctx_bb);

  test = 0;

  while (!test) {
    if (period > 0)
      lld_bb_driver_direct(&test_control_bb, &ch_pwm_bb, period);
    else if (period < 0)
      lld_bb_driver_reverse(&test_control_bb, &ch_pwm_bb, period);
    else
      lld_bb_driver_off(&test_control_bb, &ch_pwm_bb);

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
        lld_bb_driver_off(&test_control_bb, &ch_pwm_bb);
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









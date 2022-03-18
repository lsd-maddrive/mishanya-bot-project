#include <tests.h>
#include <lld_bb_driver.h>
#include <lld_bridge_system.h>
#include <serial.h>

#define PWM_FREQ 1000000
#define PWM_PERIOD 1000

#define DIRECT PAL_LINE(GPIOB,3)
#define REVERSE PAL_LINE(GPIOB,4)
#define PWM1 PAL_LINE(GPIOA,8) //TIM_CH1
#define PWM2 PAL_LINE(GPIOA,7) //TIM_CH1N

const pwm_channel_t ch_pwm_bb = {
    .ch_pwm_1 = 0,
    .ch_pwm_2 = 0,
    .alt_func_1 = 1,
    .alt_func_2 = 1
};

const pwm_ctx_t pwm_ctx_bb = {
  .pwm_ch = ch_pwm_bb,
  .driver_ptr = &PWMD1,
  .pwm_conf = {
    .frequency = PWM_FREQ,
    .period    = PWM_PERIOD,
    .callback  = NULL,
    .channels  = {
      {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
      {.mode = PWM_OUTPUT_DISABLED, NULL},
      {.mode = PWM_OUTPUT_DISABLED, NULL},
      {.mode = PWM_OUTPUT_DISABLED, NULL}
    },
    .cr2        = 0,
    .bdtr = 0b11010110,
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
    char sym=0;
    int16_t duty_cycle = 0;
    int16_t delta = 100;
    lld_bb_init_driver(&test_control_bb);
    debug_stream_init();
    //systime_t time = chVTGetSystemTime();
    while(1)
    {
        sym = sdGetTimeout(&SD3, TIME_IMMEDIATE);
        switch(sym)
        {
            case 'a':
                duty_cycle += delta;
                break;
            case 'd':
                duty_cycle -= delta;
                break;
            default: ;
        }
        if(duty_cycle > 0)
            lld_bb_driver_direct(&test_control_bb, &ch_pwm_bb, duty_cycle);
    	else if (duty_cycle < 0)
	    //duty_cycle < 0, because PWM_PERIOD+(-duty_cycle)
      	    lld_bb_driver_reverse(&test_control_bb, &ch_pwm_bb,(PWM_PERIOD+duty_cycle));
        else
            lld_bb_driver_off(&test_control_bb, &ch_pwm_bb);
	dbgprintf("duty_cycle:%d\n\r",(int)duty_cycle);
	//time = chThdSleepUntilWindowed (time, TIME_MS2I(200)+time);
    }
}






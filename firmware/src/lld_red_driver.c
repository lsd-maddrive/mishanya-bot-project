#include <lld_red_driver.h>
#include "serial.h"


void lld_red_init_driver(const arm_t *arm)
{

	dbgprintf("RED_INIT\r\n");
	control_driver_t pins = arm->arm_control;

    palSetLineMode(pins.PWM_1, PAL_MODE_ALTERNATE(1));

    palSetLineMode(pins.down, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(pins.up, PAL_MODE_OUTPUT_PUSHPULL);

    pwm_ctx_t pwm_ctx = arm->arm_ctx;

    pwmStart(pwm_ctx.driver_ptr, &pwm_ctx.pwm_conf);

}

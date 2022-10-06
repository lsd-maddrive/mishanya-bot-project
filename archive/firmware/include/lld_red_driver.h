#ifndef INCLUDE_LLD_RED_DRIVER_H
#define INCLUDE_LLD_RED_DRIVER_H

#include <common.h>
#include "lld_bridge_system.h"


void lld_red_init_driver(const line_driver_t* pins, const pwm_ctx_t* pwm_ctx);
void lld_red_driver_direct(const control_driver_t *control, const pwm_channel_t *pwm_ch, uint16_t period);
void lld_red_driver_reverse(const control_driver_t *control, const pwm_channel_t *pwm_ch, uint16_t period);
void lld_red_driver_off(const control_driver_t *control, const pwm_channel_t *pwm_ch);



#endif

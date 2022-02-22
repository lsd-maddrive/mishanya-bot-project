#ifndef FIRMWARE_INCLUDE_LLD_BB_DRIVER_H_
#define FIRMWARE_INCLUDE_LLD_BB_DRIVER_H_

#include "common.h"
#include "arm_driver.h"

void lld_bb_init_driver(const line_driver_t* pins, const pwm_ctx_t* pwm_ctx);
void lld_bb_driver_direct(const control_driver_t *control, const pwm_channel_t *pwm_ch, uint16_t period);
void lld_bb_driver_reverse(const control_driver_t *control, const pwm_channel_t *pwm_ch, uint16_t period);
void lld_bb_driver_off(const control_driver_t *control, const pwm_channel_t *pwm_ch);

#endif  // FIRMWARE_INCLUDE_LLD_BB_DRIVER_H_

#ifndef INCLUDE_LLD_BB_DRIVER_H
#define INCLUDE_LLD_BB_DRIVER_H

#include <common.h>
#include "lld_bridge_system.h"

/**
 * @brief   initialize bridge driver type bb
 * @brief   recieve control struct
 */
void lld_bb_init_driver(const control_driver_t *control);
/**
 * @brief the function open bridge driver in first direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_bb_driver_direct(const control_driver_t *control, const pwm_channel_t *pwm_ch, uint16_t period);
/**
 * @brief the function open bridge driver in second direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_bb_driver_reverse(const control_driver_t *control, const pwm_channel_t *pwm_ch, uint16_t period);
/**
 * @brief the function disables the selected direction
 * @brief recieve control struct, pwm channel
 */
void lld_bb_driver_off(const control_driver_t *control, const pwm_channel_t *pwm_ch);

#endif

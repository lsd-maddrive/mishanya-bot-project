#ifndef INCLUDE_LLD_BB_DRIVER_H
#define INCLUDE_LLD_BB_DRIVER_H

#include <common.h>
#include "lld_bridge_system.h"

/**
 * @brief   initialize bridge driver type bb
 * @brief   recieve control struct
 */
void lld_bb_init_driver(void);
/**
 * @brief the function open bridge driver in first direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_bb_driver_direct(const control_driver_t *control, uint16_t period);
/**
 * @brief the function open bridge driver in second direction
 * @brief recieve control struct, pwm channel and and the filling period
 */
void lld_bb_driver_reverse(const control_driver_t *control, uint16_t period);
/**
 * @brief the function disables the selected direction
 * @brief recieve control struct, pwm channel
 */
void lld_bb_driver_off(const control_driver_t *control);

void lld_set_diver_bb_direct(uint16_t period, type_wheel wheel_t);
void lld_set_diver_bb_reverse(uint16_t period, type_wheel wheel_t);
void lld_set_diver_bb_off(type_wheel wheel_t);
#endif

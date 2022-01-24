#ifndef INCLUDE_LLD_RED_DRIVER_H
#define INCLUDE_LLD_RED_DRIVER_H

#include <common.h>
#include <arm_driver.h>


void lld_red_init_driver(const arm_t *arm);
void lld_red_driver_up(arm_side_t side, const driver_ctx_t *arm_driver, uint16_t period);
void lld_red_driver_down(arm_side_t side, const driver_ctx_t *arm_driver, uint16_t period);
void lld_red_driver_off(arm_side_t side, const driver_ctx_t *arm_driver);



#endif

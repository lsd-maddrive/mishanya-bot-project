#ifndef INCLUDE_ELBOW_DRIVER_H
#define INCLUDE_ELBOW_DRIVER_H

#include <common.h>
#include <arm_driver.h>

void elbow_init(void);
void elbow_up(arm_side_t side, uint16_t period);

#endif

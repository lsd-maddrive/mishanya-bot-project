#ifndef INCLUDE_TRAJECTORY_H_
#define INCLUDE_TRAJECTORY_H_

#include "test.h"
#include "serial.h"
#include <stdlib.h>
#include "stdint.h"
#include <arm_kinematic.h>
#include "arm_control_system.h"
#include "arm_encoder.h"
#include "elbow_driver.h"
/**
 * @brief
 * @details
 * @note
 * @param[in]
 * @param[in]
 * @return
 */
angles_t sim_trajectory(angles_t x);

#endif

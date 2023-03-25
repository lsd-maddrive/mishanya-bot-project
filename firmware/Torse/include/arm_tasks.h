//
// Created by Anton on 05.12.2022.
//

#ifndef TORSE_ARM_TASKS_H
#define TORSE_ARM_TASKS_H

#include "common.h"
#include "elbow_driver.h"
#include "horizontal_shoulder_driver.h"
#include "vertical_shoulder_driver.h"
#include "arm_proto_gui.h"

void arm_tasks_init(SerialDriver* serial_port);

#endif //TORSE_ARM_TASKS_H

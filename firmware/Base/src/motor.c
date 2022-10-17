#include "motor.h"
#include "cnfg_peripherals.h"

control_driver_t motor_1;
control_driver_t motor_2;
control_driver_t motor_3;

void lld_motor_init(type_motor motor_n)
{
    cnfg_init();
    if(motor_n == MOTOR_1)
    {
        lld_bb_init_driver(&motor_1, &PWMD1, M1_CH_H1L1, &PWMD1, M1_CH_H2L2);
    }
}
void lld_motor(type_motor motor_n, float duty_cycle)
{
    if(motor_n == MOTOR_1)
        lld_bb_driver_direct(&motor_1, duty_cycle);
}

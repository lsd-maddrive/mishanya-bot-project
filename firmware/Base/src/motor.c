#include "motor.h"
#include "cnfg_peripherals.h"

#define K_PERCENT PWM_PERIOD/100

control_driver_t motor_1;
control_driver_t motor_2;
control_driver_t motor_3;

/**
 * @brief motor selection and set duty cycle
 * @args ptr structure control_driver_t, duty cycle
 */
void SetMotor(control_driver_t* driver, float duty_cycle);

void lldMotorInit(type_motor motor_n)
{
        cnfgInit();
        if (motor_n == MOTOR_1) {
            lld_bb_init_driver(&motor_1, &PWMD1, M1_CH_H1L1, &PWMD1, M1_CH_H2L2);
        }
        if (motor_n == MOTOR_2) {
            lld_bb_init_driver(&motor_2, &PWMD8, M2_CH_H1L1, &PWMD8, M2_CH_H2L2);
        }
        if (motor_n == MOTOR_3) {
            lld_bb_init_driver(&motor_3, &PWMD8, M3_CH_H1L1, &PWMD1, M3_CH_H2L2);
        }
}
void lldSetMotorPower(type_motor motor_n, float duty_cycle,int8_t flag_percent)
{
    if (flag_percent)
        duty_cycle = duty_cycle * K_PERCENT;
    if (motor_n == MOTOR_1)
        SetMotor(&motor_1, duty_cycle);
    else if (motor_n == MOTOR_2)
        SetMotor(&motor_2, duty_cycle);
    else if (motor_n == MOTOR_3)
        SetMotor(&motor_3, duty_cycle);
}
void SetMotor(control_driver_t* driver, float duty_cycle)
{
    if (duty_cycle > 0) {
        lld_bb_driver_direct(driver, duty_cycle);
    }
    else if (duty_cycle < 0) {
        lld_bb_driver_reverse(driver, -duty_cycle);
    }
    else if (duty_cycle == 0) {
        lld_bb_driver_off(driver);
    }
}

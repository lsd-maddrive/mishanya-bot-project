#ifndef FIRMWARE_LLD_BRIDGE_SYSTEM_H
#define FIRMWARE_LLD_BRIDGE_SYSTEM_H

#include "common.h"

#define POWER_SATURATION 0.8F

#define    ONCE_SHOULDER 0
#define    LEFT_BRIDGE_SHOULDER 0
#define    RIGHT_BRIDGE_SHOULDER 1

typedef enum {
	BB = 0,
	RED = 1
} driver_t;

typedef struct {

    union
    {
        struct {
          ioline_t          pwm_hin;
          ioline_t          pwm_lin;
        }bb_driver_line;

        struct {
          ioline_t          pwm_line;
          ioline_t          direct_line;
          ioline_t          reverse_line;
        }red_driver_line;
    };
    
    uint8_t           ch_pwm_num;
} line_driver_t;

typedef struct {
  PWMDriver         *driver_ptr;                        // PWM pointer
  line_driver_t     control;                            // typedef (search for description in this file)
} pwm_ctx_t;

typedef struct{
    union
    {
        struct {
            pwm_ctx_t         bb_pwm_ctx[2];             // typedef (search for description in this file)
        } control_bb;

        struct {
            pwm_ctx_t         red_pwm_ctx;             // typedef (search for description in this file)
        } control_red;
    };

    uint16_t pwm_period;
} control_driver_t;

#endif //FIRMWARE_LLD_BRIDGE_SYSTEM_H

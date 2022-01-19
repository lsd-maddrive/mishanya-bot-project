#include <lld_red_driver.h>


void lld_red_init_driver(driver_ctx_t *ctx) 
{

    arm_t pins = ctx->pins;

    palSetLineMode(
        pins.PWM_1, (2 << 0) | (1 << 7)
    );

    palSetLineMode(
        pins.PWM_1, (2 << 0) | (1 << 7) // TODO - refactor
    );

    palSetLineMode(
        pins.down, (1 << 0) // TODO - refactor
    );
    
    palSetLineMode(
        pins.up, (1 << 0) // TODO - refactor
    );

    pwm_ctx_t &pwm_ctx = ctx->pwm_ctx;

    if (!pwm_ctx->is_started) 
    {
        pwmStart(pwm_ctx->driver_ptr, &pwm_ctx->pwm_conf);
        pwm_ctx->is_started = true;
    }

}

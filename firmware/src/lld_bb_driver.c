



void lld_bb_init_driver(driver_ctx_t *ctx) {

    PWMConfig pwm_conf = {
        .frequency = ctx->freq,
        .period    = ctx->period,
        .callback  = NULL,
        .channels  = {
                    {.mode = RIGHT_ACTIVE_1	,   .callback = NULL},
                    {.mode = LEFT_ACTIVE_1,     .callback = NULL},
                    {.mode = RIGHT_ACTIVE_2,    .callback = NULL},
                    {.mode = LEFT_ACTIVE_2,     .callback = NULL}
                    },
        .cr2        = 0,
        .dier       = 0
    };

    arm_t pins = ctx->pins;

    palSetLineMode(
        pins.PWM_1, (2 << 0) | (1 << 7)
    );
    palSetLineMode(
        pins.PWM_1, (2 << 0) | (1 << 7) // TODO - refactor
    );
    palSetLineMode(
        pins.PWM_2, (2 << 0) | (1 << 7)
    );
    palSetLineMode(
        pins.PWM_2, (2 << 0) | (1 << 7) // TODO - refactor
    );

    palSetLineMode(
        pins.down, (1 << 0) // TODO - refactor
    );
    palSetLineMode(
        pins.up, (1 << 0) // TODO - refactor
    );

    pwmStart(ctx->driver_ptr, &pwm_conf);
}
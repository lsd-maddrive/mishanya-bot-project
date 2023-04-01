#include "lld_red_driver.h"


/**
* @brief   initialize bridge driver type red
* @brief   recieve pin struct and pwm struct
*/
void lld_red_init_driver(
    control_driver_t* driver,
    ioline_t direct_line,
    ioline_t reversr_line,
    PWMDriver* pwm_ptr,
    uint8_t ch_num
)
{
    driver->control_red.red_pwm_ctx.control.red_driver_line.direct_line = direct_line;
    driver->control_red.red_pwm_ctx.control.red_driver_line.reverse_line = reversr_line;
    driver->control_red.red_pwm_ctx.driver_ptr = pwm_ptr;
    driver->control_red.red_pwm_ctx.control.ch_pwm_num = ch_num;
    driver->pwm_period = pwm_ptr->period;
    }

/**
* @brief the function open bridge driver in first direction
* @brief recieve control struct, pwm channel and and the filling period
*/
void lld_red_driver_direct(control_driver_t* driver, float period)
{
    line_driver_t control = driver->control_red.red_pwm_ctx.control;

    palWriteLine(control.red_driver_line.reverse_line, PAL_LOW);
    palWriteLine(control.red_driver_line.direct_line, PAL_HIGH);

    PWMDriver* pwm_ptr = driver->control_red.red_pwm_ctx.driver_ptr;

    pwmEnableChannel(pwm_ptr, control.ch_pwm_num, (uint16_t)(period*POWER_SATURATION));
}

/**
* @brief the function open bridge driver in second direction
* @brief recieve control struct, pwm channel and and the filling period
*/
void lld_red_driver_reverse(control_driver_t* driver, float period)
{
    line_driver_t control = driver->control_red.red_pwm_ctx.control;

    palWriteLine(control.red_driver_line.reverse_line, PAL_HIGH);
    palWriteLine(control.red_driver_line.direct_line, PAL_LOW);

    PWMDriver* pwm_ptr = driver->control_red.red_pwm_ctx.driver_ptr;

    pwmEnableChannel(pwm_ptr, control.ch_pwm_num, (uint16_t)(period*POWER_SATURATION));
}

/**
 * @brief the function disables the selected direction
 * @brief recieve control struct, pwm channel
 */
void lld_red_driver_off(control_driver_t* driver)
{
    line_driver_t control = driver->control_red.red_pwm_ctx.control;

    PWMDriver* pwm_ptr = driver->control_red.red_pwm_ctx.driver_ptr;

    pwmDisableChannel(pwm_ptr, control.ch_pwm_num);
}

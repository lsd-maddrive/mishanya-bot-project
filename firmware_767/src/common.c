#include <common.h>

/**
 * @brief Overflow protection
 * @args duty_cycle is varible to be checked
 * @args low is minimum value
 * @args high is maximum value
 * @return duty_cycle
 */
int32_t Check(int32_t duty_cycle, int32_t low,int32_t high)
{
    if(duty_cycle<low)
    {
        duty_cycle = low;
    }
    else if(duty_cycle>=high)
    {
        duty_cycle = high;
    }
    return duty_cycle;
}



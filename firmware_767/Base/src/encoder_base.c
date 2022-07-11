#include <encoder_base.h>

#define MAX_TIC 360
int8_t status_phase_B = 0;
static bool init_enc = false;
int16_t tic_count = 0;
float rev_count = 0;
bool direction_rotation = 0;
int8_t type_enc = 0;

phase_pin encoder_1 =
{
     .line_phase_A = PAL_LINE(GPIOA,4),
     .line_phase_B = PAL_LINE(GPIOA,3)
};

phase_pin encoder_2 =
{
     .line_phase_A = PAL_LINE(GPIOF,3),
     .line_phase_B = PAL_LINE(GPIOF,5)
};

phase_pin encoder_3 =
{
     .line_phase_A = PAL_LINE(GPIOF,1),
     .line_phase_B = PAL_LINE(GPIOF,2)
};
/**
 * @brief handler interrupt
 */
static void extcb(void* args)
{
    args = args;

    if(type_enc == ENCODER_1)
    {
       status_phase_B = palReadLine(encoder_1.line_phase_B);
    }
    else if(type_enc == ENCODER_2)
    {
       status_phase_B = palReadLine(encoder_2.line_phase_B);
    }
    else if(type_enc == ENCODER_3)
    {
       status_phase_B = palReadLine(encoder_3.line_phase_B);
    }

    if(status_phase_B == 0)
    {
        direction_rotation = 1;
        tic_count+=1;
    }
    else if(status_phase_B == 1)
    {
        direction_rotation = 0;
        tic_count-=1;
    }
    if(abs(tic_count) >= MAX_TIC)
    {
        tic_count=0;
        if(direction_rotation == 1)
        {
            rev_count+=1;
        }
        else if(direction_rotation == 0)
        {
            rev_count-=1;
        }
    }
}

void lldEncoderInit(void)
{
    if(init_enc)
    return;
    if(type_enc == ENCODER_1)
    {
        palEnableLineEvent(encoder_1.line_phase_A, PAL_MODE_INPUT_PULLDOWN);
        palEnableLineEvent(encoder_1.line_phase_A, PAL_EVENT_MODE_RISING_EDGE);
        palSetLineCallback(encoder_1.line_phase_A, extcb, NULL);
    }
    else if(type_enc == ENCODER_2)
    {
        palEnableLineEvent(encoder_2.line_phase_A, PAL_MODE_INPUT_PULLDOWN);
        palEnableLineEvent(encoder_2.line_phase_A, PAL_EVENT_MODE_RISING_EDGE);
        palSetLineCallback(encoder_2.line_phase_A, extcb, NULL);
    }
    else if(type_enc == ENCODER_3)
    {
        palEnableLineEvent(encoder_3.line_phase_A, PAL_MODE_INPUT_PULLDOWN);
        palEnableLineEvent(encoder_3.line_phase_A, PAL_EVENT_MODE_RISING_EDGE);
        palSetLineCallback(encoder_3.line_phase_A, extcb, NULL);
    }
    init_enc = true;
}

int16_t GetEncoderRawTicks(void)
{
    return tic_count;
}

bool GetEncoderDirection(void)
{
    return direction_rotation;
}

float GetEncoderRawRevs(void)
{
    return (rev_count + (float)tic_count/(float)MAX_TIC);
}

void ResetEncoder(void)
{
    direction_rotation = 0;
    tic_count = 0;
    rev_count = 0;
}

void GetTypeEncoder(int8_t encoder)
{
    type_enc = encoder;
}

#include <encoder_base.h>

#define MAX_TIC 360
int8_t status_phase_B = 0;

encoder_t encoder_1 =
{
     .line_phase_A = PAL_LINE(GPIOA,4),
     .line_phase_B = PAL_LINE(GPIOA,3),
     .direction_rotation = 0,
     .tic_count = 0,
     .rev_count = 0
};

encoder_t encoder_2 =
{
     .line_phase_A = PAL_LINE(GPIOF,3),
     .line_phase_B = PAL_LINE(GPIOF,5),
     .direction_rotation = 0,
     .tic_count = 0,
     .rev_count = 0
};

encoder_t encoder_3 =
{
     .line_phase_A = PAL_LINE(GPIOF,1),
     .line_phase_B = PAL_LINE(GPIOF,2),
     .direction_rotation = 0,
     .tic_count = 0,
     .rev_count = 0
};

/**
 * @brief handler interrupt
 */
static void ExtEnc1(void* args)
{
    args = args;
    ProcessEncoderData(&encoder_1);
}

static void ExtEnc2(void* args)
{
    args = args;
    ProcessEncoderData(&encoder_2);
}

static void ExtEnc3(void* args)
{
    args = args;
    ProcessEncoderData(&encoder_3);
}


void ProcessEncoderData(encoder_t* enc_t)
{
    status_phase_B = palReadLine(enc_t->line_phase_B);
    if(status_phase_B == 0)
    {
        enc_t->direction_rotation = 1;
        enc_t->tic_count+=1;
    }
    else if(status_phase_B == 1)
    {
        enc_t->direction_rotation = 0;
        enc_t->tic_count-=1;
    }
    if(abs(enc_t->tic_count) >= MAX_TIC)
    {
        enc_t->tic_count=0;
        if(enc_t->direction_rotation == 1)
        {
            enc_t->rev_count+=1;
        }
        else if(enc_t->direction_rotation == 0)
        {
            enc_t->rev_count-=1;
        }
    }
}

void lldEncoderInit(type_encoder encoder_n)
{
    if(encoder_n == ENCODER_1)
    {
        palEnableLineEvent(encoder_1.line_phase_A, PAL_MODE_INPUT_PULLDOWN);
        palEnableLineEvent(encoder_1.line_phase_A, PAL_EVENT_MODE_RISING_EDGE);
        palSetLineCallback(encoder_1.line_phase_A, ExtEnc1, NULL);
    }
    else if(encoder_n == ENCODER_2)
    {
        palEnableLineEvent(encoder_2.line_phase_A, PAL_MODE_INPUT_PULLDOWN);
        palEnableLineEvent(encoder_2.line_phase_A, PAL_EVENT_MODE_RISING_EDGE);
        palSetLineCallback(encoder_2.line_phase_A, ExtEnc2, NULL);
    }
    else if(encoder_n == ENCODER_3)
    {
        palEnableLineEvent(encoder_3.line_phase_A, PAL_MODE_INPUT_PULLDOWN);
        palEnableLineEvent(encoder_3.line_phase_A, PAL_EVENT_MODE_RISING_EDGE);
        palSetLineCallback(encoder_3.line_phase_A, ExtEnc3, NULL);
    }
}

int16_t GetEncoderRawTicks(type_encoder encoder_n)
{
    int16_t tc = 0;
    if(encoder_n == ENCODER_1)
    {
        tc = encoder_1.tic_count;
    }
    else if(encoder_n == ENCODER_2)
    {
        tc = encoder_2.tic_count;
    }
    else if(encoder_n == ENCODER_3)
    {
         tc = encoder_3.tic_count;
    }
    return tc;
}

bool GetEncoderDirection(type_encoder encoder_n)
{
     bool dr = 0;
     if(encoder_n == ENCODER_1)
     {
         dr = encoder_1.direction_rotation;
     }
     else if(encoder_n == ENCODER_2)
     {
         dr = encoder_2.direction_rotation;
     }
     else if(encoder_n == ENCODER_3)
     {
         dr = encoder_3.direction_rotation;
     }
    return dr;
}

float GetEncoderRawRevs(type_encoder encoder_n)
{
     float rev = 0;
     encoder_t cur_encoder;
     if(encoder_n == ENCODER_1)
     {
         cur_encoder = encoder_1;
     }
     else if(encoder_n == ENCODER_2)
     {
         cur_encoder = encoder_2;
     }
     else if(encoder_n == ENCODER_3)
     {
         cur_encoder = encoder_3;
     }
     rev = getRevs(&cur_encoder);
     return rev;
}

float getRevs(encoder_t* cur_encoder)
{
    float revs = 0;
    revs = cur_encoder->rev_count +(float)cur_encoder->tic_count/(float)MAX_TIC;
    return revs;
}

void ResetEncoder(type_encoder encoder_n)
{
     if(encoder_n == ENCODER_1)
     {
         encoder_1.direction_rotation = 0;
         encoder_1.tic_count = 0;
         encoder_1.rev_count = 0;
     }
     else if(encoder_n == ENCODER_2)
     {
         encoder_2.direction_rotation = 0;
         encoder_2.tic_count = 0;
         encoder_2.rev_count = 0;
     }
     else if(encoder_n == ENCODER_3)
     {
         encoder_3.direction_rotation = 0;
         encoder_3.tic_count = 0;
         encoder_3.rev_count = 0;
     }
}


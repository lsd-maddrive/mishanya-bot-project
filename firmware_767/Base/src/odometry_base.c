#include <encoder_base.h>
#include <odometry_base.h>

#define VTIME_PERIOD_MS 10
#define MS_TO_SEC 100
#define FILTER
#define Kf 0.4

static virtual_timer_t odometr_1;
static virtual_timer_t odometr_2;
static virtual_timer_t odometr_3;

coeffwheelshaft Kw = 2 * M_PI * Wheel_Radius * k;
float prev_dist = 0;
float rev_count = 0;
float filtered_speed = 0;
float prev_filtered_speed = 0;
static bool init_tim = 0;

odometry_var odmtr_enc1=
{
    .dist = 0,
    .prev_dist = 0,
    .speed = 0,
    .filtered_speed = 0,
    .prev_filtered_speed = 0
};

odometry_var odmtr_enc2=
{
    .dist = 0,
    .prev_dist = 0,
    .speed = 0,
    .filtered_speed = 0,
    .prev_filtered_speed = 0
};

odometry_var odmtr_enc3=
{
    .dist = 0,
    .prev_dist = 0,
    .speed = 0,
    .filtered_speed = 0,
    .prev_filtered_speed = 0
};
/**
 * @brief handler interrupt of virtual timer
 */
static void tim_enc1(void* encdrs)
{
    odometry_var *encdr = (odometry_var*)encdrs;
    handler_odomety(encdr,CM,ENCODER_1);
    chSysLockFromISR();
    chVTSetI(&odometr_1, TIME_MS2I(VTIME_PERIOD_MS), tim_enc1, &odmtr_enc1);
    chSysUnlockFromISR();
}

static void tim_enc2(void* encdrs)
{
    odometry_var *encdr = (odometry_var*)encdrs;
    handler_odomety(encdr, CM,ENCODER_2);
    chSysLockFromISR();
    chVTSetI(&odometr_2, TIME_MS2I(VTIME_PERIOD_MS), tim_enc2, &odmtr_enc2);
    chSysUnlockFromISR();
}

static void tim_enc3(void* encdrs)
{
    odometry_var *encdr = (odometry_var*)encdrs;
    handler_odomety(encdr, CM,ENCODER_3);
    chSysLockFromISR();
    chVTSetI(&odometr_3, TIME_MS2I(VTIME_PERIOD_MS), tim_enc3, &odmtr_enc3);
    chSysUnlockFromISR();
}
void odometryInit(void)
{
    if(init_tim)
      return;
    lldEncoderInit(ENCODER_1);
    lldEncoderInit(ENCODER_2);
    lldEncoderInit(ENCODER_3);
    chVTObjectInit(&odometr_1);
    chVTSet(&odometr_1, TIME_MS2I(VTIME_PERIOD_MS), tim_enc1, &odmtr_enc1);
    chVTObjectInit(&odometr_2);
    chVTSet(&odometr_2, TIME_MS2I(VTIME_PERIOD_MS), tim_enc2, &odmtr_enc2);
    chVTObjectInit(&odometr_3);
    chVTSet(&odometr_3, TIME_MS2I(VTIME_PERIOD_MS), tim_enc3, &odmtr_enc3);
    init_tim = TRUE;
}

distanceCrossWheel odometryGetWheelDistance(DistUnits units, type_encoder encoder)
{
    rev_count = GetEncoderRawRevs(encoder);
    return rev_count * Kw * units;
}

speedOdometry odometryGetWheelSpeed(SpeedUnits units,type_encoder encoder)
{
    float spd_wheel = 0;
    if(encoder == ENCODER_1)
        spd_wheel = odmtr_enc1.speed;
    else if(encoder == ENCODER_2)
        spd_wheel = odmtr_enc2.speed;
    else if(encoder == ENCODER_3)
        spd_wheel = odmtr_enc3.speed;
    return spd_wheel*units;
}

void odometryReset(type_encoder encoder)
{
    if(encoder == ENCODER_1)
    {
        odmtr_enc1.speed = 0;
    }
    else if(encoder == ENCODER_2)
    {
        odmtr_enc2.speed = 0;
    }
    else if(encoder == ENCODER_3)
    {
        odmtr_enc3.speed = 0;
    }
}

void handler_odomety(odometry_var *encdr, DistUnits units, type_encoder encoder)
{
    encdr->dist = odometryGetWheelDistance(units, encoder)/units;
    encdr->speed = (encdr->dist - encdr->prev_dist)*MS_TO_SEC;
    encdr->prev_dist = encdr->dist;
    #ifdef FILTER
        encdr->filtered_speed = encdr->speed * (1 - Kf) + Kf * encdr->prev_filtered_speed;
        encdr->prev_filtered_speed = encdr->filtered_speed;
        encdr->speed = encdr->filtered_speed;
    #endif
}

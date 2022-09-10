#ifndef INCLUDE_ODOMETRY_BASE_H_
#define INCLUDE_ODOMETRY_BASE_H_

#include <common.h>

#define Wheel_Radius 1
#define k 1

typedef enum {MM = 1000, CM = 100, M = 1}DistUnits;
typedef enum {MM_S = 1000, CM_S = 100, M_S = 1}SpeedUnits;
typedef float coeffwheelshaft;
typedef float distanceCrossWheel;
typedef float speedOdometry;

/**
 * @brief structure for odometry of wheel
 * @identifier1 wheel distance
 * @identifier2 previous distance
 * @identifier3 wheel speed
 * @identifier4 speed after filter
 * @identifier5 previous after filter
 */
typedef struct
{
    float dist;
    float prev_dist;
    float speed;
    float filtered_speed;
    float prev_filtered_speed;
}odometry_var;
/**
 * @brief Initialization virtual timer
 * @note period 10ms
 */
void odometryInit(void);

/**
 * @brief Get distance traveled by the wheel
 * @args units(MM, CM, M)
 * @return distance
 */
distanceCrossWheel odometryGetWheelDistance(DistUnits uints, type_encoder encoder);

/**
 * @brief Get speed of wheel
 * @args units(MM_S, CM_S, M_S)
 * @return speed
 */
speedOdometry odometryGetWheelSpeed(SpeedUnits units,type_encoder encoder);

/**
 * @brief Reset the value of speed
 * @args encoder is value from enum
 */
void odometryReset(type_encoder encoder);


/**
 * @brief odometry calculation function
 * @args encdr is pointer to the structure
 * @args unit of measurement
 * @args encoder is value from enum
 */
void handler_odomety(odometry_var *encdr, DistUnits units, type_encoder encoder);

#endif

#ifndef INCLUDE_ARM_KINEMATIC_H_
#define INCLUDE_ARM_KINEMATIC_H_

#include <math.h>
#include <common.h>
#include <serial.h>
#include <test.h>

/**
 * @brief   Invalidates the data cache lines overlapping a memory buffer.
 * @details This function is meant to make sure that data written in
 *          data cache is invalidated.
 * @note    On devices without data cache this function does nothing.
 * @note    The function does not consider the lower 5 bits of addresses,
 *          the buffers are meant to be aligned to a 32 bytes boundary or
 *          adjacent data can be invalidated as side effect.
 *
 * @param[in] saddr     start address of the DMA buffer
 * @param[in] n         size of the DMA buffer in bytes
 *
 * @api
 */

#define PI 3.1415926535
#define DEG2RAD 0.0174532925
#define RAD2DEG 57.2957795131
struct coord{
    float x;
    float y;
    float z;
};

struct angles{
    float th1;
    float th2;
    float th3;
};

typedef struct angles angles_t;
typedef struct coord coord_t;

struct arm{
  bool side;
  float shoulder;
  float forearm;
  coord_t coord_base;
};

typedef struct arm arm_t;

/**
 * @brief   Forward kinematics function.
 * @details A function that takes three angles and calculates the
 *          coordinates of the grip point.
 * @note    The function calculates the position of the grip point
 *          in the absolute coordinate system, the beginning of which
 *          is specified in the "arm_t" structure.
 * @note    Restrictions are imposed on the corners, in case of
 *          violation of which the function will return zeros.
 * @note    Angles are accepted in radians, coordinates are returned
 *          in meters.
 *
 * @param[in] arm     Structure with hand option and parameters,
 * @param[in] ang     Three angles
 * @return            Three coordinates
 */

coord_t arm_dir_kinematic(arm_t arm, angles_t ang);

/**
 * @brief   Invers kinematics function.
 * @details A function that takes three coordinates and calculates
 *          the rotation angle of the links..
 * @note    The function calculates the angles in the absolute
 *          coordinate system, the origin of which is specified
 *          in the "arm_t" structure.
 * @note    Restrictions are imposed on the angles, if violated, 180
 *          degrees are returned.
 * @note    Coordinates are accepted in meters, angles are returned
 *          in radians.
 *
 * @param[in] arm     Structure with hand option and parameters,
 * @param[in] coord   Three coordinates
 * @return            Three angles
 */

angles_t arm_inv_kinematic(arm_t arm, coord_t coord);

#endif

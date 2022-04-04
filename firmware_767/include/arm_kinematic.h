#ifndef INCLUDE_ARM_KINEMATIC_H_
#define INCLUDE_ARM_KINEMATIC_H_

#include <math.h>
#include <common.h>

/**
 * @brief   Math constants.
 * @note    Pi, conversion factors from degrees to radians and from
 *          radians to degrees.
 */

#define PI 3.1415926535
#define DEG2RAD 0.0174532925
#define RAD2DEG 57.2957795131

/**
 * @brief   Structures for coordinates.
 */

struct coord{
    float x;
    float y;
    float z;
};

/**
 * @brief   Structures for angles.
 */

struct angles{
    float th1;
    float th2;
    float th3;
};

typedef struct angles angles_t;
typedef struct coord coord_t;

/**
 * @brief   Structure for hand parameters.
 * @note    side - calculate a left or right hand, shoulder - shoulder
 *          length(L1), forearm - forearm length(L2), coord_base -
 *          shoulder point coordinates in absolute coordinate system.
 */

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

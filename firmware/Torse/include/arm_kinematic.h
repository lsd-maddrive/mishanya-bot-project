#ifndef TORSE_ARM_KINEMATIC_H
#define TORSE_ARM_KINEMATIC_H

#include <math.h>
#include "joint.h"
#include "common.h"
#include "macro_lib.h"

/**
 * @brief   Structures for coordinates. unit of measurement: meter
 */
typedef struct{
    float x;
    float y;
    float z;
}coord_t;

/**
 * @brief   Structures for angles. unit of measurement: radians
 */
typedef struct{
    float th1;
    float th2;
    float th3;
}angles_t;

/**
 * @brief   Structures for arm sizes. unit of measurement: meter
 */
typedef struct{
    float shoulder_length;
    float forearm_length;
}length_t;

/**
 * @brief   Structure for hand parameters.
 * @note    side - calculate a left or right hand, shoulder_length - shoulder
 *          length in meter(L1), forearm_length - forearm length in meter(L2),
 *          coord_base - shoulder point coordinates in absolute coordinate system.
 */
typedef struct{
    length_t arm_length;
    coord_t coord_base;
}arm_kinematic_t;

typedef enum{
    ERROR_NONE = 0,
    ERROR_NEGATIVE_DISCRIMINANT = 1,
    ERROR_FALSE_LENGTH = 2,
    ERROR_SIDE = 3
}kinematic_error_t;

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

kinematic_error_t arm_direct_kinematic(arm_kinematic_t* arm, angles_t* angles, coord_t* coord_position, arm_side_t side);

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

kinematic_error_t arm_inverse_kinematic(arm_kinematic_t* arm, coord_t* coord, angles_t* arm_angles, arm_side_t side);


#endif //TORSE_ARM_KINEMATIC_H

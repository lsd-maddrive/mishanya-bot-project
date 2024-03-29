#include "arm_kinematic.h"

static void sin_angle_calculation(angles_t* angles, angles_t* sin_angles);
static void cos_angle_calculation(angles_t* angles, angles_t* cos_angles);
static void angle_transform_calculation(angles_t* angles, float deg_or_rad);
static uint8_t check_solution(angles_t* angles, arm_angle_limits_t* angles_limits);
static uint8_t angle_calculation(arm_kinematic_t* arm, angles_t* angles, coord_t* coord, int8_t sign, float d, float A, float B, float D, float discriminant);

void sin_angle_calculation(angles_t* angles, angles_t* sin_angles)
{
  sin_angles->th1 = sinf(angles->th1);
  sin_angles->th2 = sinf(angles->th2);
  sin_angles->th3 = sinf(angles->th3);
}

void cos_angle_calculation(angles_t* angles, angles_t* cos_angles)
{
  cos_angles->th1 = cosf(angles->th1);
  cos_angles->th2 = cosf(angles->th2);
  cos_angles->th3 = cosf(angles->th3);
}

void angle_transform_calculation(angles_t* angles, float deg_or_rad)
{
  angles->th1 *= deg_or_rad;
  angles->th2 *= deg_or_rad;
  angles->th3 *= deg_or_rad;
}

uint8_t angle_calculation(arm_kinematic_t* arm, angles_t* angles, coord_t* coord, int8_t sign, float d, float A, float B, float D, float discriminant)
{
  float shoulder_length = arm->arm_length.shoulder_length;
  float forearm_length = arm->arm_length.forearm_length;

  float xm;
  float ym;

  // check first solution
  ym = ((-2)*D*B + (float)sign*sqrtf(discriminant))/(2*(A*A + B*B));
  xm = sqrtf(shoulder_length*shoulder_length - ym*ym);

  angles->th1 = atan2f(ym,xm);
  angles->th2 = PI - acosf((shoulder_length*shoulder_length + forearm_length*forearm_length - d)/(2*shoulder_length*forearm_length));
  angles->th3 = (PI/2) - atan2f(((-1)*(coord->x*ym - xm*coord->y)),sqrtf((xm*coord->z)*(xm*coord->z) + (ym*coord->z)*(ym*coord->z)));

  angle_transform_calculation(angles, RAD2DEG);

  return check_solution(angles, &arm->arm_angle_limits);
}

uint8_t check_solution(angles_t* angles, arm_angle_limits_t* angles_limits)
{
  return CHECK_IN_RANGE(angles->th1, angles_limits->th1->min_angle, angles_limits->th1->max_angle) &
         CHECK_IN_RANGE(angles->th2, angles_limits->th2->min_angle, angles_limits->th2->max_angle) &
         CHECK_IN_RANGE(angles->th3, angles_limits->th3->min_angle, angles_limits->th3->max_angle);
}

kinematic_error_t arm_direct_kinematic(arm_kinematic_t* arm, angles_t* angles, coord_t* coord_position, arm_side_t side)
{
  float shoulder_length = arm->arm_length.shoulder_length;
  float forearm_length = arm->arm_length.forearm_length;

  angle_transform_calculation(angles, DEG2RAD);

  angles_t sin_angles;
  angles_t cos_angles;

  sin_angle_calculation(angles, &sin_angles);
  cos_angle_calculation(angles, &cos_angles);

  coord_position->x = (cos_angles.th1*(shoulder_length + cos_angles.th2 * forearm_length)) -
                      (cos_angles.th3*(sin_angles.th1*sin_angles.th2)) * forearm_length;

  coord_position->y = (sin_angles.th1*(shoulder_length + cos_angles.th2 * forearm_length)) +
                      (cos_angles.th1*(cos_angles.th3*sin_angles.th2)) * forearm_length;

  coord_position->z = (sin_angles.th2*sin_angles.th3) * forearm_length;

  if (side == LEFT){
    coord_position->z = ((-1)*coord_position->z) - arm->coord_base.z;
  }
  else if(side == RIGHT)
  {
    coord_position->z -= arm->coord_base.z;
  }
  else
  {
    return ERROR_SIDE;
  }

  coord_position->x -= arm->coord_base.x;
  coord_position->y -= arm->coord_base.y;

  return ERROR_NONE;
}


kinematic_error_t arm_inverse_kinematic(arm_kinematic_t* arm, coord_t* coord, angles_t* arm_angles, arm_side_t side)
{
  float shoulder_length = arm->arm_length.shoulder_length;
  float forearm_length = arm->arm_length.forearm_length;

  coord->x += arm->coord_base.x;
  coord->y += arm->coord_base.y;

  if (side == LEFT){
    coord->z = ((-1)*coord->z) + arm->coord_base.z;
  }
  else if(side == RIGHT)
  {
    coord->z += arm->coord_base.z;
  }
  else
  {
    return ERROR_SIDE;
  }

  // auxiliary variables
  float A = (-2)*coord->x;
  float B = (-2)*coord->y;

  float d = coord->x*coord->x +
            coord->y*coord->y +
            coord->z*coord->z;

  float D = shoulder_length*shoulder_length -
            forearm_length*forearm_length +
            d;

  if (sqrtf(d) > (shoulder_length+forearm_length))
  {
    return ERROR_FALSE_LENGTH;
  }
  else
  {
    float discriminant = (2*D*B)*(2*D*B) - 4*(A*A + B*B)*(D*D - (A*shoulder_length)*(A*shoulder_length));
    if (discriminant < 0)
    {
      return ERROR_NEGATIVE_DISCRIMINANT;
    }
    else
    {
      if(angle_calculation(arm, arm_angles, coord, 1, d, A, B, D, discriminant) == 1)
      {
        return ERROR_NONE;
      }

      if(angle_calculation(arm, arm_angles, coord, -1, d, A, B, D, discriminant) == 1)
      {
        return ERROR_NONE;
      }

      return ERROR_FALSE_LENGTH;

    }
  }
}
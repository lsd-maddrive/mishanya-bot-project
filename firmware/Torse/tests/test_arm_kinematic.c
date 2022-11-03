#include "test.h"
#include "serial.h"
#include "arms.h"





void test_arm_kinematic(void)
{
  debug_stream_init();
  arms_init();
  coord_t target_coordinates = {
          .x = 0.3f,
          .y = 0.2f,
          .z = 0.2f

  };

  arm_set_coordinates(RIGHT, &target_coordinates);

//  if(arm_inverse_kinematic(&arm_kinematic, &target_coordinates, &target_angles, LEFT)
//  while(1)
//  {
//
//  }
}


#include <arm_kinematic.h>

arm_t right_arm = {
                   .side = 0,
                   .shoulder = 1,
                   .forearm = 2,
                   .coord_base = {
                                  .x = 0.7,
                                  .y = -0.2,
                                  .z = 1
              }
};
arm_t left_arm = {
                  .side = 1,
                  .shoulder = 1,
                  .forearm = 2,
                  .coord_base = {
                                 .x = 0.7,
                                 .y = -0.2,
                                 .z = -1
                  }
};

void test_arm_kinematic(void){
  debug_stream_init();
  coord_t b = {
                .x = 0.7372,
                .y = 0.8195,
                .z = 0.2247
  };
  angles_t theta = arm_inv_kinematic(left_arm, b);
  theta.th1 = theta.th1*RAD2DEG;
  theta.th2 = theta.th2*RAD2DEG;
  theta.th3 = theta.th3*RAD2DEG;
  dbgprintf("Test 1: \r\n");
  dbgprintf("th1 = %.4f th2 = %.4f th3 = %.4f \r\n", theta.th1, theta.th2, theta.th3);
  coord_t position = arm_dir_kinematic(left_arm, theta);
  dbgprintf("x = %.4f y = %.4f z = %.4f \r\n", position.x, position.y, position.z);

  angles_t a = {
                .th1 = 30,
                .th2 = 45,
                .th3 = 60
  };
  coord_t position1 = arm_dir_kinematic(left_arm, a);
  dbgprintf("Test 2: \r\n");
  dbgprintf("x = %.4f y = %.4f z = %.4f \r\n", position1.x, position1.y, position1.z);
  angles_t theta1 = arm_inv_kinematic(left_arm, position1);
  dbgprintf("th1 = %.4f th2 = %.4f th3 = %.4f \r\n", theta1.th1*RAD2DEG, theta1.th2*RAD2DEG, theta1.th3*RAD2DEG);
  while(1){

  }
}

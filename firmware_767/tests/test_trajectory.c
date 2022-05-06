#include <trajectory.h>
arm_t left_arm1 = {
                   .side = LEFT_ARM,
                   .shoulder_length = 0.3,
                   .forearm_length = 0.265,
                   .coord_base = {
                                  .x = 0,
                                  .y = 0,
                                  .z = 0
              }
};
uint8_t arm = 0;

static THD_WORKING_AREA(traking_elbow,256);

static THD_FUNCTION(elbow_update,arg) {
  (void *) arg;
  systime_t time = chVTGetSystemTimeX();
  while (1) {
    elbow_update_angle(0.00002);
    time = chThdSleepUntilWindowed(time, TIME_MS2I(20)+time);
  }

}

void test_trajectory()
{
  chThdCreateStatic(traking_elbow,sizeof(traking_elbow),NORMALPRIO-2,
                      elbow_update, NULL);
  debug_stream_init();
  arm_encoder_t encoder;
  encoder = elbow_get_encoder_ctx(LEFT_ELBOW);
  encoder_init(&encoder);
  float e1 = 0; float e2 = 0; float e3 = 0;
  float th_real = 0;
//  angles_t th_real;
  angles_t theta; coord_t b;
//  float a[12];
  float a[4];
//  float flag[3] = {300, 300, 300};
  float flag = 300;
  sdGet(&SD3);//ќжидание получение данных
  while(1)
  {
//    sdRead(&SD3, (uint8_t *)a, 48);//12*4=48
//    sdRead(&SD3, (uint8_t *)a, 16);
    a[1] = 5;
    a[2] = 20;
    a[3] = 10;
    a[4] = 30;
    chThdSleepMilliseconds(20);
//    for (int i = 0; i < 12; i = i + 3)
    for (int i = 0; i < 4; i++)
    {
//      b.x = a[i];
//      b.y = a[i+1];
//      b.z = a[i+2];
//      theta = arm_inv_kinematic(left_arm1, b);
//      theta.th1 = theta.th1  * RAD2DEG;
//      theta.th2 = theta.th2  * RAD2DEG;
//      theta.th3 = theta.th3  * RAD2DEG;
      theta.th1 = 0;
      theta.th2 = a[i];
      theta.th3 = 0;
      arm = LEFT_ELBOW;
//      elbow_set_angle((float)theta.th2, arm);
      elbow_set_angle((float)theta.th2, arm);
      do
      {
//        th_real = sim_trajectory(theta);
        th_real = encoder_read(&encoder);
//        e1 = fabs(th_real.th1 - theta.th1);
//        e2 = fabs(th_real.th2 - theta.th2);
        e2 = fabs(th_real - theta.th2);
//        e3 = fabs(th_real.th3 - theta.th3);
//        sdWrite(&SD3, (uint8_t *)&th_real, 12);
//        sdWrite(&SD3, (uint8_t *)&th_real, 4);
        dbgprintf("angle=%.4f\r\n", th_real);
      }while((e2 >= 0.01));//while((e1 >= 0.01)&&(e2 >= 0.01)&&(e3 >= 0.01));
    }
//    sdWrite(&SD3, (uint8_t *)flag, 12);//¬озвращаем число, которое будет знаком о прекращении движени€
    sdWrite(&SD3, (uint8_t *)&flag, 4);

  }
}

//angles_t real_ang = {
//                 .th1 = 0,
//                 .th2 = 0,
//                 .th3 = 0
//};
//
//angles_t sim_trajectory(angles_t x)
//{
//  real_ang.th1 = (0.5*real_ang.th1 + 0.5*x.th1);//»митаци€ апериодического звена
//  real_ang.th2 = (0.5*real_ang.th2 + 0.5*x.th2);
//  real_ang.th3 = (0.5*real_ang.th3 + 0.5*x.th3);
//  return real_ang;
//}

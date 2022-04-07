#include <arm_kinematic.h>

float s_th1;
float s_th2;
float s_th3;
float c_th1;
float c_th2;
float c_th3;
float x;
float y;
float z;

coord_t arm_dir_kinematic(arm_t arm, angles_t ang)
{
  coord_t set_pos;
  float L1 = arm.shoulder_length;
  float L2 = arm.forearm_length;
  float alpha = ang.th1 * DEG2RAD;
  float betta = ang.th2  * DEG2RAD;
  float gamma = ang.th3  * DEG2RAD;
  s_th1 = sin(alpha);
  s_th2 = sin(betta);
  s_th3 = sin(gamma);
  c_th1 = cos(alpha);
  c_th2 = cos(betta);
  c_th3 = cos(gamma);
  set_pos.x = (c_th1*(L1 + c_th2 * L2)) - (c_th3*(s_th1*s_th2)) * L2;
  set_pos.y = (s_th1*(L1 + c_th2 * L2)) + (c_th1*(c_th3*s_th2)) * L2;
  set_pos.z = (s_th2*s_th3) * L2;
  if (arm.side == LEFT_ARM){
    set_pos.z = ((-1)*set_pos.z) - arm.coord_base.z;
  }
  else
  {
    set_pos.z = set_pos.z - arm.coord_base.z;
  }
  set_pos.x = set_pos.x - arm.coord_base.x;
  set_pos.y = set_pos.y - arm.coord_base.y;
  return set_pos;
}
angles_t arm_inv_kinematic(arm_t arm, coord_t coord)
{
  angles_t set_ang_1;
  angles_t set_ang_2;
  float L1 = arm.shoulder_length;
  float L2 = arm.forearm_length;
  float x = coord.x + arm.coord_base.x;
  float y = coord.y + arm.coord_base.y;
  float z;
  if (arm.side == LEFT_ARM){
     z = (-1)*(coord.z + arm.coord_base.z);
  }
  else z = (coord.z + arm.coord_base.z);
  float A = (-2)*x;
  float B = (-2)*y;
  float d = x*x + y*y + z*z;
  float D = L1*L1 - L2*L2 + d;
  float ym1; float ym2; float xm1; float xm2;
  float Discr;
  if (sqrt(d) > (L1+L2)){
    set_ang_1.th1 = PI;
    set_ang_1.th2 = PI;
    set_ang_1.th3 = PI;
    set_ang_2.th1 = set_ang_1.th1;
    set_ang_2.th2 = set_ang_1.th1;
    set_ang_2.th3 = set_ang_1.th1;
  }
  else{
    Discr = (2*D*B)*(2*D*B) - 4*(A*A + B*B)*(D*D - (A*L1)*(A*L1));
    if (Discr < 0){
      set_ang_1.th1 = PI;
      set_ang_1.th2 = PI;
      set_ang_1.th3 = PI;
      set_ang_2.th1 = set_ang_2.th1;
      set_ang_2.th2 = set_ang_2.th1;
      set_ang_2.th3 = set_ang_2.th1;
    }
    else{
      ym1 = ((-2)*D*B + sqrt(Discr))/(2*(A*A + B*B));
      ym2 = ((-2)*D*B - sqrt(Discr))/(2*(A*A + B*B));
      xm1 = sqrt(L1*L1 - ym1*ym1);
      xm2 = sqrt(L1*L1 - ym2*ym2);
      set_ang_1.th1 = atan2(ym1,xm1);
      set_ang_2.th1 = atan2(ym2,xm2);
      set_ang_1.th2 = PI - acos((L1*L1 + L2*L2 - d)/(2*L1*L2));
      set_ang_2.th2 = set_ang_1.th2;
      set_ang_1.th3 = (PI/2) - atan2(((-1)*(x*ym1 - xm1*y)),sqrt((xm1*z)*(xm1*z) + (ym1*z)*(ym1*z)));
      set_ang_2.th3 = (PI/2) - atan2(((-1)*(x*ym2 - xm2*y)),sqrt((xm2*z)*(xm2*z) + (ym2*z)*(ym2*z)));
    }
  }
//  return set_ang_1;
  return set_ang_2;
}

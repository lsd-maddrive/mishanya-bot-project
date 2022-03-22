function f = kinematic_hand(x0, y0, z0, L1, L2)
A = -2*x0;
B = -2*y0;
C = -2*z0;
d = x0^2 + y0^2 + z0^2;
D = -(L2^2) + L1^2 + d;
ym1 = (-2*D*B + sqrt((2*D*B)^2 - 4*(A^2 + B^2)*(D^2 - (A^2)*(L1^2))))/(2*(A^2 + B^2));
ym2 = (-2*D*B - sqrt((2*D*B)^2 - 4*(A^2 + B^2)*(D^2 - (A^2)*(L1^2))))/(2*(A^2 + B^2));

xm1 = sqrt(L1^2 - ym1^2);
xm2 = sqrt(L1^2 - ym2^2);

th1_1 = atan2(ym1, xm1);
th1_2 = atan2(ym2, xm2);

th3_1 = (pi/2) - atan2(-(x0*ym1 - xm1*y0),sqrt((xm1*z0)^2+(ym1*z0)^2));
th3_2 = (pi/2) - atan2(-(x0*ym2 - xm2*y0),sqrt((xm2*z0)^2+(ym2*z0)^2));

th2 = pi - acos((L1^2 + L2^2 - d)/(2*L1*L2));
f = [th1_1, th2, th3_1; th1_2, th2, th3_2];
end
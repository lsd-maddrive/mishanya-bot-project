clear, clc;
syms O1 O2 O3 L1 L2
a2 = [L1+L2*cos(O2); L2*sin(O2); 0];
R = [1 0 0; 0 cos(O3) -sin(O3); 0 sin(O3) cos(O3)];
a2_1 = R*a2
R1 = [cos(O1) -sin(O1) 0; sin(O1) cos(O1) 0; 0 0 1];
a2_2 = R1*a2_1

% syms O1 O2 O3 L1 L2 x_1 y_1 z_1
% x_h = L1*sin(O1) + L2*sin(O1 + O2)
% y_h = L1*cos(O1) + L2*cos(O1 + O2)
% R = [(cos(O3)+(1 - cos(O3))*(x_1)^2) ((1 - cos(O3))*x_1*y_1-sin(O3)*z_1) ((1-cos(O3))*x_1*z_1 + sin(O3)*y_1);...
%     ((1-cos(O3))*y_1*x_1 + sin(O3)*z_1) (cos(O3)+(1 - cos(O3))*(y_1)^2) ((1-cos(O3))*y_1*z_1 - sin(O3)*x_1);...
%     ((1-cos(O3))*z_1*x_1 + sin(O3)*y_1) ((1-cos(O3))*z_1*y_1 + sin(O3)*x_1) (cos(O3)+(1 - cos(O3))*(z_1)^2)]
% R = subs(R, {x_1, y_1, z_1}, [sin(O1), cos(O1), 0])
% XYZ = R*[x_h; y_h; 0]
% % x = XYZ(1)
% % y = XYZ(2)
% % z = XYZ(3)
% % ex_XYZ = expand(XYZ)
% % XYZ
% simpl_XYZ = simplify(XYZ)
% x = simpl_XYZ(1)
% y = simpl_XYZ(2)
% z = simpl_XYZ(3)

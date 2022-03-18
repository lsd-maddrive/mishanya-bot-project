clear, clc;
syms x_a1 y_a1 x_a2 y_a2 z_a2 x_j y_j z_j x y z x1 y1 z1 x2 y2 z2 x3 y3 z3 x_m y_m z_m
M = [(x - x1) (x2 - x1) (x3 - x1);...
    (y - y1) (y2 - y1) (y3 - y1);...
    (z - z1) (z2 - z1) (z3 - z1)]
M1 = subs(M, {x1, y1, z1, x2, y2, z2, x3, y3, z3}, [0, 0, 0, x_m, y_m, 0, x_a2, y_a2, z_a2])
xyz_1 = det(M1)
% M2 = subs(M, {x1, y1, z1, x2, y2, z2, x3, y3, z3}, [0, 0, 0, x_m, y_m, 0, 1, 1, 0])
% xyz_2 = det(M2)
x_n1 = subs(xyz_1, {x, y, z}, [1, 0, 0])
y_n1 = subs(xyz_1, {x, y, z}, [0, 1, 0])
z_n1 = subs(xyz_1, {x, y, z}, [0, 0, 1])
% x_n2 = subs(xyz_2, {x, y, z}, [1, 0, 0])
% y_n2 = subs(xyz_2, {x, y, z}, [0, 1, 0])
% z_n2 = subs(xyz_2, {x, y, z}, [0, 0, 1])
x_n2 = 0
y_n2 = 0
z_n2 = 1
cos_ang = ((x_n1*x_n2 + y_n1*y_n2 + z_n1*z_n2))/(sqrt(x_n1^2 + y_n1^2 + z_n1^2)*sqrt(x_n2^2 + y_n2^2 + z_n2^2))
function f = kinematic_dir_hand(O1, O2, O3, L1, L2)
O1 = O1*(pi/180);
O2 = O2*(pi/180);
O3 = O3*(pi/180);
x = cos(O1)*(L1 + L2*cos(O2)) - L2*cos(O3)*sin(O1)*sin(O2);
y = sin(O1)*(L1 + L2*cos(O2)) + L2*cos(O1)*cos(O3)*sin(O2);
z = L2*sin(O2)*sin(O3);
f = [x; y; z];
end
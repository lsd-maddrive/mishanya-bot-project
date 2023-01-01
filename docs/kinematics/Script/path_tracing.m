robot = rigidBodyTree('DataFormat','column','MaxNumBodies',3);

shoulder_length  = 0.258;
forearm_length  = 0.236;

body = rigidBody('v_shoulder');
joint = rigidBodyJoint('v_shoulder_joint', 'revolute');
setFixedTransform(joint,trvec2tform([0 0 0]));
joint.JointAxis = [0 0 1];
joint.PositionLimits = [-0.3 0.79];
body.Joint = joint;
addBody(robot, body, 'base');

body = rigidBody('h_shoulder');
joint = rigidBodyJoint('h_shoulder_joint', 'revolute');
setFixedTransform(joint,trvec2tform([0 0 0]));
joint.JointAxis = [1 0 0];
joint.PositionLimits = [-0.09 0.82];
body.Joint = joint;
addBody(robot, body, 'v_shoulder');

body = rigidBody('forearm');
joint = rigidBodyJoint('forearm_joint','revolute');
setFixedTransform(joint, trvec2tform([shoulder_length,0,0]));
joint.JointAxis = [0 0 1];
joint.PositionLimits = [0.8 1.5];
body.Joint = joint;
addBody(robot, body, 'h_shoulder');

body = rigidBody('brush');
joint = rigidBodyJoint('fix1','fixed');
setFixedTransform(joint, trvec2tform([forearm_length, 0, 0]));
body.Joint = joint;
addBody(robot, body, 'forearm');

showdetails(robot)

ik = inverseKinematics('RigidBodyTree', robot);
weights = [0, 0, 0, 1, 1, 1];
endEffector = 'brush';

q0 = homeConfiguration(robot);
qInitial = q0; % Use home configuration as the initial guess

point = [0.3 0.2 0.1];
qSol = ik(endEffector,trvec2tform(point),weights,qInitial);


show(robot,qSol,'PreservePlot',false);

drawnow

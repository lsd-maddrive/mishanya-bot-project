robot = rigidBodyTree('DataFormat','column','MaxNumBodies',3);

shoulder_length  = 0.3;
forearm_length  = 0.265;

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

points = [0.5 0.5 0.1 ; 0.4 0.4 0.1 ; 0.3 0.3 0.0; 0.2 0.2 0.0; 0.1 0.1 0.0];

qInitial = q0; % Use home configuration as the initial guess
for i = 1:5
    % Solve for the configuration satisfying the desired end effector
    % position
    point = points(i,:);
    qSol = ik(endEffector,trvec2tform(point),weights,qInitial);
    % Store the configuration
    qs(i,:) = qSol;
    % Start from prior solution
    qInitial = qSol;
end

framesPerSecond = 5;
r = rateControl(framesPerSecond);
for i = 1:5
    show(robot,qs(i,:)','PreservePlot',false);
    drawnow
    waitfor(r);
end

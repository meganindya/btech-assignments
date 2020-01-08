% Find phase angle of (3 + 4i) in radian and degree

clc; clear;

A = 3 + 4i;
fprintf('Number:\t');
disp(A);

rad = angle(A);           % general output is by ddefault in radians
fprintf('\nAngle in Radians:\t');
disp(rad);

deg = rad * (180 / pi);   % you know this much of mathematics
fprintf('\nAngle in Degrees:\t');
disp(deg);
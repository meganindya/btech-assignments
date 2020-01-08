% generic quadratic polynomial roots question, I ain't gonna type

clc; clear;

A = [1 5 6];
fprintf('Coefficients:\t');
disp(A);

fprintf('\nRoots using Formula: ');
B = rootsQuadratic(A);    % function definition in rootsQuadratic.m
disp(B);                  % type conversion

fprintf('\nRoots using function:');
disp(roots(A)');          % built-in function




% THAT'S ALL FOLKS !
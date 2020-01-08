% A complex square matrix A is normal if A* . A = A . A*
% where A* is the conjugate transpose of A.
% Find which one of A, B, C are normal

clc; clear;

load('matrices.mat');

checkNormal(A);       % function definition in checkNormal.m
checkNormal(B);
checkNormal(C);
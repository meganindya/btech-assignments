% A complex square matrix A is unitary if A* . A = A . A* = I
% where I is identity matrix.
% Find which one of A, B, C are unitary.

clc; clear;

load('matrices.mat');

checkUnitary(A);      % function definition in checkUnitary.m
checkUnitary(B);
checkUnitary(C);
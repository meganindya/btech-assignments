% Hermitian matrix (or self-adjoint matrix) is a square matrix with
% complex entries that is equal to its own conjugate transpose


% given matrices A, B, C are saved in matrices.mat, don't ask how

clc; clear;

load('matrices.mat');   % yeah, that's how you load

checkHermitian(A);      % function definitions in checkHermitian.m
checkHermitian(B);
checkHermitian(C);
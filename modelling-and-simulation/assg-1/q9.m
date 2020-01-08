% Multiply two matrices with size 3 x 1

clc; clear;

A = randi(10, 3, 1);
fprintf('Matrix A :\n');
disp(A);

B = randi(10, 3, 1);
fprintf('\nMatrix B :\n');
disp(B);

prod_A_B = A .* B;    % .* does individual product of respective terms
fprintf('\nA .x B :\n');
disp(prod_A_B);
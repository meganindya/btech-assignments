% Multiply two matrices of sizes 3 x 3

clc; clear;

A = round(rand(3) * 5);   % or use randi(5, 3), just the same
fprintf('Matrix A :\n');
disp(A);

B = round(rand(3) * 5);   % or use randi(5, 3), in fact randi is better
fprintf('\nMatrix B :\n');
disp(B);

prod_A_B = A * B;
fprintf('\nA x B :\n');
disp(prod_A_B);
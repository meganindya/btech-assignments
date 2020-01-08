% Generate a 20 x 20 random matrix A with values between 0 to 255
% a) calculate the mean of the elements
% b) generate a binary matrix from A by replacing its elements
%    by '0' and '1' if element is < mean and > mean, respectively

clc; clear;

A = randi(255, 20);
fprintf('Matrix :\n');
disp(A);

fprintf('\nMean of all elements :');
mean_A = mean(mean(A));   % mean on a non 1D matrix generates column wise mean
disp(mean_A);

fprintf('\nNew Binary Matrix :\n');
B = A > mean_A;           % evaluates for each element in A, result in binary
disp(B);
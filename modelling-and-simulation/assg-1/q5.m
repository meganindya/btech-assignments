% Generate a 20 x 20 random matrix A with values between 0 to 255
% a) introduce jth row by computing the average of ith row and (i + j)th row
% b) introduce jth column by computing the average of ith column and (i + j)th column
% c) sampling by this process and make the matrix of size 39 x 39

clc; clear;

A = randi(255, 20);
fprintf('Matrix :\n');
disp(A);

fprintf('\nRow-wise introduction :\n');
for I = 1 : 19
    A = [A; (A(I, :) + A(I + 1, :)) / 2]; % adds new row at end. This is a bad technique.
end
disp(A);

fprintf('\nColumn-wise introduction :\n');
for I = 1 : 19
    A = [A, (A(:, I) + A(:, I + 1)) / 2]; % adds new column at end. This is a bad technique.
end
disp(A);

% for new row / column introduction, first allocate fresh memory using zeros() function
% following by assigning to respective positions. Dynamic allocation bottlenecks for
% bigger matrices; depends on hardware.


% HONESTLY have no idea, if this solution was asked !
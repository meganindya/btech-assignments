% Create an identity matrix of size 4 x 4. Can you delete the second column
% of the matrix? (function : eye())

clc; clear;

A = eye(4);   % 4 x 4 identity matrix
fprintf('4 x 4 Identity Matrix:\n');
disp(A);

% No, I can't delete the second column. However, I can show you something that
% apprears like I deleted the second column.

fprintf('2nd col deleted :\n');
A = [A(:, 1), A(:, 3 : 4)];   % reallocates memory of a matrix with same no of rows
disp(A);                      % but column 1 concatenated with 3 - 4 in same variable
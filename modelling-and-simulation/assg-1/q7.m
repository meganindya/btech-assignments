% Generate a 20 x 20 random matrix A with values between 0 to 255
% a) divide it into 3 x 3 overlapping blocks
% b) for each block generate a binary number using the following logic
%    logic: if value > middle value replace it by '1' otherwise replace it by '0'.
%    do it in anticlockwise fashion starting from the left side

clc; clear;

A = randi(255, 20);
fprintf('Matrix :\n');
disp(A);

for I = 1 : 18
    for J = 1 : 18
        B = A(I : I + 2, J : J + 2);    % 3 x 3 matrix of i to (i + 2) row and j to (j + 2) row
        fprintf('\nBlock from (%d : %d) x (%d : %d) :\n', I, I + 2, J, J + 2);
        C = B > B(2,2);   % see Q4b
        disp(C);       % didn't go for the anticlockwise thing coz this works fine a.f.
    end
end
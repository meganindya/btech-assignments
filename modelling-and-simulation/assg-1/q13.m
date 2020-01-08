% Compute the trigonometric series sin(x) = x - (x^3 /3!) + (x^5 / 5!) - (x^7 / 7!).
% what is the unit of the result?

clc; clear;

x = -pi : 0.1 : pi;
y = sin_x(x);           % function declaration in sin_x.m
fprintf('(x, sin(x)): \n');
for I = 1 : size(x, 2)  % size with DIM 2 gives no of columns
    fprintf('(%ld,\t%ld)\n', x(I), y(I));
end

  % not asked, but just to show the deviation
figure('name', 'Sin curve comparison with its Taylor expansion', 'numbertitle', 'off');
plot(x, sin(x), 'r', x, y, 'b');
axis([-pi pi -1 1]);
title('Sin curves');




% THAT'S ALL FOLKS !
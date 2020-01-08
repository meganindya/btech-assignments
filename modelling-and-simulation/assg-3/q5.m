clear; clc;

X = -5 : 0.5 : 5;
Y = -5 : 0.5 : 5;
[X, Y] = meshgrid(X, Y); % returns 2D grid coordinates based on the coordinates contained in X and Y

Z1 = 10 - 3 * X - 2 * Y;
Z2 = (X + Y + 3) / 2;
Z3 = 2 * X + Y - 1;

figure('name', '3D Plot', 'numbertitle', 'off');
hold on;
surf(X, Y, Z1);
surf(X, Y, Z2);
surf(X, Y, Z3);
hold off;
colormap(jet);    % try for summer, winter, automn, spring :P; all work
title('3x + 2y + z = 10;  x + y - 2z = -3;  2x + y - z = 1');
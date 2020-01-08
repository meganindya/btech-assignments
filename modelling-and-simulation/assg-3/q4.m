clear; clc;

X = -5 : 0.01 : 5;
Y1 = (7 - 2 * X) / 3;
Y2 = (1 - 5 * X) / 2;

figure('name', 'Linear Equations', 'numbertitle', 'off');
plot(X , Y1, 'r', X, Y2, 'b', 'linewidth', 2);
hold on;          % retains current plot and certain axes properties
title('2x + 3y = 7 ,  5x + 2y = 1');  % so that subsequent graphing commands add to the existing graph
axis square;      % grid shapping square (compare with 'equal')
axis([-5 5 -5 5]);
xlabel('X axis');
ylabel('Y axis');
grid on;
grid minor;       % for minor grids
set(gca,'xtick',[-5 : 5 : 5]);  % x axis minor grid spacing
set(gca,'ytick',[-5 : 5 : 5]);  % y axis minor grid spacing
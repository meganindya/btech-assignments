clear; clc;

X = 1 : 10;
Y = 3 * X + 5;

figure('name', 'Line', 'numbertitle', 'off');
plot(X , Y, 'r', 'linewidth', 2);
title('y  =  3x  +  5');
xlim([1 10]);             % read the question
xlabel('X axis');
ylim([1 40]);
ylabel('Y axis');
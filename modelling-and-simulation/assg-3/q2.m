clear; clc;

X = 0 : pi / 200 : 2 * pi;
Y1 = 2 * cos(X);
Y2 = cos(X);
Y3 = 0.5 * cos(X);

figure('name', 'Comparing sin curves', 'numbertitle', 'off');
plot(X , Y1, 'r', X, Y2, 'b', X, Y3, 'm', 'linewidth', 2);
title('2cos(x),  cos(x), $\frac{cos(x)}{2}$', 'Interpreter', 'latex');  % same again, #OnlyForPros, MATLAB only, not  GNU Octave
axis([0 2 * pi -2.25 2.25]);
xlabel('X axis');
ylabel('Y axis');
clear; clc;

X = 0 : 0.5 : 35;
Y = X .^ 3;

figure('name', 'Function 1', 'numbertitle', 'off');
plot(X, Y, 'r.', 'MarkerSize', 8);
title('y  =  ${x}^{3}$', 'Interpreter', 'latex');
axis square;
xlabel('Time(t)');
ylabel('Amp(A)');
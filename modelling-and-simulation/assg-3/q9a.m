clear; clc;

X = 0 : 0.5 : 35;
Y = 50 ./ X;

figure('name', 'Function 1', 'numbertitle', 'off');
plot(X, Y, 'r.', 'MarkerSize', 8);
title('y  =  ${x}^{-\frac{1}{{x}^\frac{1}{16}}}$', 'Interpreter', 'latex');
axis square;
xlabel('Time(t)');
ylabel('Amp(A)');
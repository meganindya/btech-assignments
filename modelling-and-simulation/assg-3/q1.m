clear; clc;

X = 0 : 0.01 : 1.5;
Y = 4 * sqrt(6 * X + 1);
Z = 5 * exp(0.3 * X) - 2 * X;

figure('name', 'Some Hyperfury Function', 'numbertitle', 'off');
plot(X , Y, 'r', X, Z, 'b', 'linewidth', 2);      % type help plot for advanced usage
title('4 * \surd{(6x + 1)} ,  5e^{0.3x} - 2x');   % this uses LaTeX, #NotForNoobs
axis([0 1.5 0 15]);                               % [Xmin Xmax Ymin Ymax]
xlabel('X axis');
ylabel('Y axis');
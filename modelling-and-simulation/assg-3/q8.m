clear; clc;

X = -1 : 0.001 : 20;
Y = stepfn(X);         % function definition in stepfn.m

figure('name', 'Unit Step Function', 'numbertitle', 'off');

subplot(3, 1, 1);
plot(X, Y, 'r', 'linewidth', 2);
title('Unit Step Function');
axis equal;
axis([-1 20 -0.5 2.5]);
xlabel('Time(t)');
ylabel('Amp(A)')

D = 10;
Y = stepfn(X + D);

subplot(3, 1, 2);
plot(X, Y, 'r', 'linewidth', 2);
title('Delayed Unit Step Function');
axis equal;
axis([-1 20 -0.5 2.5]);
xlabel('Time(t)');
ylabel('Amp(A)');

Y = 2 * stepfn(X);

subplot(3, 1, 3);
plot(X, Y, 'r', 'linewidth', 2);
title('Step Function with Amplitude 2');
axis equal;
axis([-1 20 -0.5 2.5]);
xlabel('Time(t)');
ylabel('Amp(A)');
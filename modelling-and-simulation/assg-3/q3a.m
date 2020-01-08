clear; clc;

X = 0 : 0.01 : 2 * pi;
Y1 = 2 * cos(X);
Y2 = cos(X);
Y3 = 0.5 * cos(X);

figure('name', 'Comparing sin curves', 'numbertitle', 'off');

subplot(3, 1, 1);                   % rows, columns, position; this statement necessary
plot(X , Y1, 'r', 'linewidth', 2);
title('2 cos(x)', 'Interpreter', 'latex');
axis([0 2 * pi -2.25 2.25]);
xlabel('X axis');
ylabel('Y axis');

subplot(3, 1, 2);
plot(X , Y2, 'r', 'linewidth', 2);
title('cos(x)', 'Interpreter', 'latex');
axis([0 2 * pi -2.25 2.25]);
xlabel('X axis');
ylabel('Y axis');

subplot(3, 1, 3);
plot(X , Y3, 'r', 'linewidth', 2);
title('$\frac{1}{2}$ cos(x)', 'Interpreter', 'latex');
axis([0 2 * pi -2.25 2.25]);
xlabel('X axis');
ylabel('Y axis');
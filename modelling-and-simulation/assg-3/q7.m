clear; clc;

X = 0 : 20;
Y = sin(X);

% was supossed to generate a zeros vector and add a ones vector
% at postions, but you know, who cares. This code's threatening already.

figure('name', 'Unit Sampled Sequence', 'numbertitle', 'off');

subplot(2, 1, 1);
hold on;
stem(X, Y, 'Marker', 'none', 'color', [1 0 0]);   % draws ordinate from given point
plot(X, Y, 'b.', 'MarkerSize', 16);
hold off;
title('sin(x)');
xlim([-1 21]);
xlabel('Time(t)');
ylim([-1.5 1.5]);
ylabel('Amplitude(A)');

D = 10;
X = X - D;        % hope you've passed signal, systems and circuits
Y = sin(X);

subplot(2, 1, 2);
hold on;
stem(X, Y, 'Marker', 'none', 'color', [1 0 0]);
plot(X, Y, 'b.', 'MarkerSize', 16);
hold off;
title('delayed function');
xlim([-1 21]);
xlabel('Time(t)');
ylim([-1.5 1.5]);
ylabel('Amplitude(A)');
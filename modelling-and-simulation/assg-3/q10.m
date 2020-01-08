clear; clc;

T = 0 : 0.2 : 50;
figure('name', 'Discrete Time Sequence');

S = funfunc(T);     % function definition in funfunc.m

subplot(3, 1, 1);
plot(T, S, 'r.', 'MarkerSize', 8);
title('S = 2m ${0.9}^{m}$', 'interpreter', 'latex');
xlabel('time(m)');
ylabel('S');

N = noise(T);       % function defintion in noise.m

subplot(3, 1, 2);
plot(T, N, 'r.', 'MarkerSize', 8);
title('Noise');
xlabel('time(m)');
ylabel('S');

Y = S + N';

subplot(3, 1, 3);
plot(T, Y, 'r.', 'MarkerSize', 8);
title('Noisy Sequence');
xlabel('time(m)');
ylabel('S');




% THAT'S ALL FOLKS !
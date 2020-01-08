% Generate a vector t_log in the range 10 to 10000 with the elements
% of the vectors spaced in logarithmic scale. Create another vector
% with random values as its elements and plot them in a x-y 2D plane
% with values of t_log in x axis. (function : logspace, rand)

clc; clear;

t_log = logspace(1, 4, 100);  % row matrix of 10 elements from 10^1 to 10^4
randm = rand(1, 100);         % 1 x 100 random matrix (real numbers in [0, 1])

figure('name', 'Question 2', 'numbertitle', 'off'); %  See titlebar of figure window
semilogx(t_log, randm);       % plot in x from t_log and in y from randm
% Generate a vector with 10 elements. Spacing between
% two consecutive elements is 2. (function : "linspace")
% a) print the vector in the command window
% b) access the third element of the vecct and print the value

clc; clear;   % clc clears command window, clear cleans workspace

A = linspace(2, 20, 10)';   % row matrix of 10 elements from 2 to 20 transposed

fprintf('Vector :\n');
disp(A);

fprintf('\n3rd element :');
disp(A(3));
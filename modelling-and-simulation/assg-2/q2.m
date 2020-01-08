% Prove by an example that the product of a complex number
% and its conjugate is a real number, and is always positive

clc; clear;

a = 3.064 + 4.141i;
fprintf('a\t= ');
disp(a);
b = conj(a);

c = a * b;
fprintf('\na * conjugate(a)\t= ');
disp(c);
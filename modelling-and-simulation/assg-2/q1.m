% Take two complex number a = 2 + 3i and b = 5 + 4i
% i)  compute c = a / b
% ii) rationalize the denominator by multiplying the numerator
%     and the denominator by the conjugate of the denominator

clc; clear;

a = 2 + 3i;
fprintf('a\t\t= %d + %dj\n', real(a), imag(a));   % real(z) is Re(z) and imag(z) is Im(z)
b = 5 + 4i;
fprintf('b\t\t= %d + %dj\n\n', real(b), imag(b));

c = a / b;
fprintf('\na / b\t= %f + %fj\n', real(c), imag(c));
fprintf('\n(after multiplication by conjugate)\n');
d = (a * conj(b)) / (b * conj(b));
fprintf('a / b\t= %f + %fj\n', real(d), imag(d));

fprintf('\n\ndid ya expect the result to change? LOL!\n');
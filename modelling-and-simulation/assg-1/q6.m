% Generate a 100 x 100 random matrix A with values between 0 to 255. Count the
% occurrence of each value of the matrix in number of times

clc; clear;

A = randi(255, 100);
fprintf('Matrix :\n');
disp(A);

B = zeros(256, 1);    % 256 row null matrix

for I = 1 : 100                           % loops for all values in A
	for J = 1 : 100                         % for value x (e.g. 137) increments
		B(A(I, J) + 1) = B(A(I, J) + 1) + 1;  % value of (x + 1)th cell (: 138) by 1
	end                                     % (x + 1) since, counting starts from 0
end

fprintf('\nFrequency :\n');
for I = 1 : 256
    fprintf('\t%d\t: %d\n', I, B(I));
end

plot(0 : 255, B);     % SIMPLY; not asked
% Create a 3 x 3 circulant matrix using the function "gallery".
% Then find the eigenvalue and eigenvector of the matrix (function : eig)

clc; clear;

a = gallery('circul', 3);   % type help gallery in the command window and read
fprintf('Matrix:\n');
disp(a);

e_val = eig(a);
[v, e_vec] = eig(a);        % type eig in command window and read that too
fprintf('\nEigen Values:\n');
disp(e_val);

fprintf('\nEigen Vectors:\n');
for I = 1 : size(e_vec, 1)
  disp(e_vec(I, I));
end


% I know you remember shit, and so do I
% Generate a 10 x 10 random matrix with vvalues betwween 0 to 100
% a) calculate row-wise mean
% b) column-wise mean of the elements
% c) find the maximum and minimum elements for both cases

clc; clear;

A = randi(100, 10);       % 10 x 10 matrix of integers in [0, 100]

fprintf('Matrix :\n');
disp(A);

fprintf('\nRow-wise Means :\n');
row_mean = mean(A, 2);    % 2 for DIM 2 i.e. columns (here mean of columns per row)
disp(row_mean);

fprintf('\nMax of Row Means :');
max_row_mean = max(row_mean);
disp(max_row_mean);

fprintf('\nMin of Row Means :');
min_row_mean = min(row_mean);
disp(min_row_mean);

fprintf('\nColumn-wise Means :\n');
col_mean = mean(A, 1);    % 2 for DIM 1 i.e. rows (here mean of rows per column)
disp(col_mean);

fprintf('\nMax of Column Means :');
max_col_mean = max(col_mean);
disp(max_col_mean);

fprintf('\nMin of Column Means :');
min_col_mean = min(col_mean);
disp(min_col_mean);
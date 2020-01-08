  % function declaration
function y = sin_x(X)
    y = X - ((X.^3)/factorial(3)) + ((X.^5)/factorial(5)) - ((X.^7)/factorial(7));
end
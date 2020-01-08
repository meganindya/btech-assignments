function Y = rootsQuadratic(X)
    Y = zeros(1, 2);
    D = sqrt(power(X(2), 2) - 4 * X(1) * X(3));
    Y(1) = (-X(2) - D) / (2 * X(1));
    Y(2) = (-X(2) + D) / (2 * X(1));
end
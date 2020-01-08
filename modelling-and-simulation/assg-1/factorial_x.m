  % function definition
function y = factorial_x(X)   % go back to computer class
    fact_v = 1;
    for I = 1 : X
        fact_v = I * fact_v;
    end
    y = fact_v;           % place final value in the return variable in declaration
end
function checkUnitary(X)
    fprintf('Matrix X:\n');
    disp(X);
    fprintf('X . X*:\n');
    A = X * transpose(conj(X));
    disp(A);
    fprintf('X* . X:\n');
    B = transpose(conj(X)) * X;
    disp(B);
    
    if isequal(isequal(A, B), eye(size(A, 1)))
        fprintf('\n-- Matrix is an Unitary Matrix');
    else
        fprintf('\n-- Matrix is NOT an Unitary Matrix');
    end;
    fprintf('\n\n---------\n\n');
end
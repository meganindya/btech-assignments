function checkNormal(X)
    fprintf('Matrix X:\n');
    disp(X);
    fprintf('\nX . X*:\n');
    A = X * transpose(conj(X));
    disp(A);
    fprintf('\nX* . X:\n');
    B = transpose(conj(X)) * X;
    disp(B);
    
    if isequal(A, B)
        fprintf('\n-- Matrix is a Normal Matrix');
    else
        fprintf('\n-- Matrix is NOT a Normal Matrix');
    end;
    fprintf('\n\n---------\n\n');
end
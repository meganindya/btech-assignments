function checkHermitian(X)
    fprintf('Matrix X:\n');
    disp(X);
    fprintf('\nConjugate Transpose:\n');
    Y = transpose(conj(X));
    disp(Y);
    
    if isequal(X, Y)
        fprintf('\n-- Matrix is a Hermitian Matrix');
    else
        fprintf('\n-- Matrix is NOT a Hermitian Matrix');
    end;
    fprintf('\n\n---------\n\n');
end
function retval = stepfn(X)
    Y = zeros(length(X), 1);
    for I = 1 : length(X)
        if X(I) >= 0
            Y(I) = 1;
        else
            Y(I) = 0;
        end;
    end;
    retval = Y;
end
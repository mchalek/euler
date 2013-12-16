count = 0;
r = 11;
R = 1:r;
for n = 23:100,
    N = 1:n; 
    nmR = 1:(n-r);
    nCr = prod(N)/(prod(R)*prod(nmR));
    while nCr > 1e6,
        r = r - 1; 
        R = 1:r;
        nmR = 1:(n-r);
        nCr = prod(N)/(prod(R)*prod(nmR));
    end;
    if n / 2 == floor(n / 2)
        count = count + 2*(n/2-r-1) + 1;
    else
        count = count + 2*(ceil(n/2)-r-1);
    end;
end;
fprintf('I counted: %g\n', count);
function tri
L = [];
tic;
mMax = (-1+sqrt(1+4e6))/2;
for m = 2:mMax,
    n = 1:min([m-1,(1e6-m^2)/m]); % start at m+1 because we don't allow zero
    L = [L, 2*m^2+2*m*n];
end;
    
fprintf('Execution time: %gs\n', toc);
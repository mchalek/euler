nmax = 100; 
A = zeros(32);

for k = 1:32,
    for a = k:32,
        A(k, a) = nchoosek(a, a-k)*(1/2)^a;
    end;
end;

AvgN = 0;
An = [zeros(31, 1); 1];
M = eye(32)-A;
for n = 1:nmax,
    AvgN = AvgN + n*sum(M*An);
    An = A * An;
end;
fprintf('%.10f\n', AvgN)

% clear;

N = 500;

A = sparse(N, N);
A(1, 2) = 1/2;
A(2, 1) = 1;
A(2, 3) = 1/2;
A(N, N-1) = 1/2;
A(N-1, N)= 1;
A(N-1, N-2) = 1/2;
for i = 3:(N-2),
    A(i, i-1) = 1/2;
    A(i, i+1) = 1/2;
end;

p = [1/3*ones(1, 500); 2/3*ones(1, 500)];
p(1, primes(500)) = 2/3;
p(2, primes(500)) = 1/3;

seq = [1 1 1 1 2 2 1 1 1 2 1 1 2 1 2];
r = ones(1, 500);
d = ones(1, 500);
for n = 0:(length(seq)-1)
    v = (3*p)*((2*A)^n);
%     v = (p)*((A)^n);
    r = r.*v(seq(n+1), :);
    d = d * 3 * 2^n;
%     for j = 1:500,
%         [r(j), d(j)] = rat(r(j)/d(j), 1e-10);
%     end;
end;

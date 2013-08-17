N = 30;
Nb = 50;

tic;
A = sparse(N^2,N^2);
for j = 1:N,
    for i = 1:N,
        a = i + (j-1)*N;
        if i > 1,
            b = i-1 + N*(j-1);
            A(a, b) = 0.25;
        end;
        if i < N,
            b = i+1 + N*(j-1);
            A(a, b) = 0.25;
        end;
        if j > 1,
            b = i + N*(j-2);
            A(a, b) = 0.25;
        end;
        if j < N,
            b = i + N*j;
            A(a, b) = 0.25;
        end;
    end;
end;

for i = 1:N^2,
    A(:, i) = A(:, i) / sum(A(:, i));
end;

Pi = ones(N^2, 1);

Pf = A^Nb*Pi;

fprintf('Execution time: %gs\n', toc);
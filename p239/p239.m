M = 3;
N = 2;
Psum = 0;
fprintf('M == %g\nN == %g\n', M, N);
for R = 0:N,
    P = nchoosek(N, R)*factorial(M-R)/factorial(M)*((M-R-1)/(M-R))^(N-R);
    Psum = Psum + P;
    fprintf('P(%g) == %.12g\n', R, P);
end;

disp(Psum);
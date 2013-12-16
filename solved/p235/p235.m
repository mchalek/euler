function p235
tic
x = fzero(@Lfz, 1.002)

fprintf('%.13g\n', x);

toc
function S = Lfz(r)

N = 5000;

rN = rn(r, N);

S = 900*(1-rN)./(1-r) - 3.*(1-(N+1)*rN + N*r*rN)./((1-r).^2) + 6e11;

return;


function S = L(r)

N = 5000;

rN = rn(r, N);

S = 900*(1-rN)./(1-r) - 3.*(1-(N+1)*rN + N*r*rN)./((1-r).^2);

return;


function x = rn(r, n)

a = r-1;

x = 1;
term = ones(size(a));
for k = 1:n,
    term = term .* a * (n-k+1) / k;
    x = x + term;
end;

return;

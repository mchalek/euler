k = 20000;
N = 1000000;

% answer is: 1 - Prob(all defects on different chips)
%              - \sum_j Prob(exactly j chips contain 2 defects, the rest < 2)
%
% formulae: 
%          P1 = \prod_{j=0}^{k-1} (N-j)/N
% 
%                          k! N!
%          P2 = -----------------------------
%                (k-2j)! (N+j-k)! N^k 2^j j!
%
% Note difficulty with precision: computed result is 1e-10 bigger than true
% answer
tic;
v = 0:(k-1);
p1 = prod((N-v)/N);

p2 = 0;
for j = 1:k/2
    h = gammaln(k+1)+gammaln(N+1)-gammaln(k-2*j+1)-gammaln(N+j-k+1)-k*log(N)-j*log(2) - gammaln(j+1);
    p2 = p2 + exp(h);
end;
toc
round((1-(p1+p2))*1e10)/1e10
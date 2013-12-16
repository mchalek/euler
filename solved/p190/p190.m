% Note: this is an easy convex optimization problem.  Transform Pm by
% taking log, and you get a convex function. Then use Lagrange multiplier
% and you're done.
%
% solution: x_k = 2*k / (m + 1).

sum = 0;
for m = 2:15,
    k = 1:m;
    xk = 2*k/(m+1);
    Pm = prod(xk.^k);
    sum = sum + floor(Pm);
end;

fprintf('your sum: %.10g\n', sum);
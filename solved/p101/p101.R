n = matrix(1:11,11,1)

poly = 1-n+n^2-n^3+n^4-n^5+n^6-n^7+n^8-n^9+n^10
#poly = n^3

M = matrix(,11,11);
for(i in 1:11) {
	M[,i] = n^(i-1)
}

ans = 0
for(i in 1:10) {
    A = M[1:i, 1:i]
    y = poly[1:i]

    x = solve(A, y)
    xpad = matrix(0,1,11)
    xpad[1:i] = x

    check = M %*% t(xpad)
    pass = abs(check-poly) < 1e-3
    FIT_ix = which(pass == F)[1]
    print(paste("index ", FIT_ix, " value ", check[FIT_ix]))

    ans = ans + check[FIT_ix]
}

print(ans)

x = seq(-5,5,0.05)
yp = sqrt(100-4*x^2)
yn = -yp

X = c(x,x)
Y = c(yn,yp)
plot(X, Y)

N = 1000
df = read.csv('~/Desktop/test.csv', header=F)
lines(df$V1[1:N], df$V2[1:N])

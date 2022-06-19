# 1.1
rep(6, 5)
# 1.2
seq(1, 20, 4)
# 1.3
pmax(rep(6, 5), seq(1, 20, 4))
# 1.4
which(c(1, 5, 2, 4, 6) >= 3)
# 1.5
t(matrix(1:12 ,3))
# 1.6
matrix(1:12,3) * matrix(1:12,3)
# 1.7
det(matrix(c((1:3) ^ 0, (1:3) ^ 1, (1:3) ^ 2),3))
# 1.8
diff(diff(diff((1:5) ^ 3)))
# 1.9
cov(c(1, 2, 3, 3), c(-2, 0, 2, 2))
# 1.10
integrate(sin, -pi, pi)

# 2.1
a <- matrix(c(1, 3, 5, 2, 4, 6, 7, 8, 9), 3)
b <- matrix(c(1, 2, 7, 2.5, 4.5, 10.3, 9, 7, 2.1), 3)
# 对应元素
a * b
# 矩阵运算
a %*% b
# 特征值
ev <- eigen(a)
ev$val

# 2.2
c <- seq(1, 99, 2)
sum(c)

#2.3
pnorm(0.1, 0, 1)
x <- seq(-5, 5, length=100)
y <- dnorm(x)
plot(x, y, type="l", ylim = range(y) * 1.1, xlim = range(x), axes = FALSE, col = "black", xlab = "", ylab = "")
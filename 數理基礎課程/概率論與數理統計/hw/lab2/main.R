t <- seq(-5, 5, 0.01)
c <- c(1, 2, 10, 50, 100)
cor <- c("red", "green", "blue", "orange", "purple")

for (i in c) {
    y <- dt(t, i)
    s <- as.character(i)
    s <- paste0("Student's t-distribution with df = ", s)
    plot(t, y, type = "l", main = s, xlab = "", ylab = "")
}

for (i in c(5, 4, 3, 2, 1)) {
    y <- dt(t, c[i])
    if (i == 5) {
        plot(t, y, type = "l", col = cor[i], main = "Student's t-distribution", xlab = "", ylab = "")
    } else {
        lines(t, y, type = "l", col = cor[i])
    }
}

legend("topright", legend = c, col = cor, lty = 1, lwd = 2)          
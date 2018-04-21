setwd("/Users/park-wanbae/Desktop/MFE/2018-1/FIN513/Homework/HW8")
dist = read.csv("prob2_distribution.csv")

plot(dist$u, dist$D, type = 'l', xlab = "Fraction", ylab = "CDF",
     ylim = c(0.8, 1))
par(new = "T")
plot(dist$u, dist$L, type = 'l', xlab = "Fraction", ylab = "CDF",
     lty = 2, ylim = c(0.8, 1))
legend(0.0, 0.05, legend=c("L", "D"),
       lty=1:2, cex=0.8)

setwd("/Users/park-wanbae/Desktop/MFE/2018-1/FIN513/Homework/HW8")
dist = read.csv("prob2_distribution.csv")

plot(dist$X...u, dist$D, type = 'l', xlab = "u", ylab = "CDF",
     ylim = c(0, 0.05))
par(new = "T")
plot(dist$X...u, dist$L, type = 'l', xlab = "u", ylab = "CDF",
     ylim = c(0, 0.05), lty = 2)
legend(0.0, 0.05, legend=c("L", "D"),
       lty=1:2, cex=0.8)

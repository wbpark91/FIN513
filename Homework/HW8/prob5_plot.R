setwd("/Users/park-wanbae/Desktop/MFE/2018-1/FIN513/Homework/HW8")
result = read.csv("problem5.csv")

plot(result$Interest, result$NPV_a, type = 'l', lty = 1,
      xlab = "Initial Interest Rate", ylab = "NPV",
      ylim = c(70, 135))
par(new = "T")
plot(result$Interest, result$NPV_b, type = 'l', lty = 2,
    ylim = c(70, 135), xlab = "Initial Interest Rate",
    ylab = "NPV")
legend(0.12, 135, legend=c("b = -30", "b = 0"),
       lty=1:2, cex=0.8)
par(new = "F")
plot(result$Interest, result$DIFF, type = 'l',
     xlab = "Initial Interest Rate", ylab = "Absolute Difference")

setwd("/Users/wanbaep2/Desktop/FIN513/Homework/HW7")
result = read.csv("problem4_result.csv")

plot(result$Maturity, result$Yield.Market., 'l',
     xlab = "Maturity", ylab = "Yield", col = 'red')
lines(result$Maturity, result$Yield.Model., 'l', col = 'blue',
      lty = 2)
legend(0, 0.0422, legend = c("Market Yield", "Model Yield"),
       col = c("red", "blue"), lty = 1:2, cex = 0.8)

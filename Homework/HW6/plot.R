library(plotrix)
setwd("/Users/wanbaep2/Desktop/FIN513/Homework/HW6")
problem2 = read.csv("problem2.csv")

plot(problem2$OPTION_PRICE, problem2$VOL, xlab = "Stock Price",
     ylab = "Volatility", type ='l',
     main = "Stock Volatility under Merton Model")

from = 5
to = 100
gap.plot(problem2$OPTION_PRICE, problem2$CEVVOL, 
         xlab = "Stock Price",
     ylab = "Volatility", type = 'l',
     gap = c(from, to),
     main = "Stock Volatility under CEV Model")
axis.break(2, from, breakcol="snow", style="gap")
axis.break(2, from*(1+0.02), breakcol="black", style="slash")
axis.break(4, from*(1+0.02), breakcol="black", style="slash")
axis(2, at=from)

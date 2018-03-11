library(plotrix)
setwd("/Users/wanbaep2/Desktop/FIN513/Homework/HW6")

# PROBLEM 2
problem2 = read.csv("problem2.csv")

plot(problem2$OPTION_PRICE, problem2$VOL, xlab = "Stock Price",
     ylab = "Volatility", type ='l',
     main = "Stock Volatility under Merton Model")

plot(problem2$OPTION_PRICE, problem2$CEVVOL, 
         xlab = "Stock Price",
     ylab = "Volatility", type = 'l',
     main = "Stock Volatility under CEV Model")

# PROBLEM 3
problem3 = read.csv("problem3.csv")

plot(problem3$VOL, problem3$MULT.100,
     xlab = "Volatility of Firm Value",
     ylab = "Volatility Multiplier",
     main = "Volatilty Multiplier, Face Value = 100",
     type = 'l')

plot(problem3$VOL, problem3$MULT.50,
     xlab = "Volatility of Firm Value",
     ylab = "Volatility Multiplier",
     main = "Volatilty Multiplier, Face Value = 50",
     type = 'l')

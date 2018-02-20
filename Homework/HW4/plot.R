setwd("/Users/wanbaep2/Desktop")
price = read.csv("prob2.csv")
plot(price$Time.to.Maturity.Month., price$Value, 
     xlim = rev(range(price$Time.to.Maturity.Month.)),
     xlab = "Time to Maturity(Month)",
     ylab = "Price",
     type = 'l',
     main = "Straddle Price")

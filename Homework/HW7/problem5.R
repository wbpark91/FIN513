setwd("/Users/wanbaep2/Desktop/FIN513/Homework/HW7")
result = read.csv("problem5.csv")
rate = read.csv("rate.csv")
hist(result$VALUE, xlab = "Value", main = "")
hist(rate$RATE, xlab = "Rate", main = "Histogram")
summary(result$VALUE)

print("Number of path which has value below zero: ")
print(sum(result$VALUE < 0))
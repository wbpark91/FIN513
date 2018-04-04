setwd("/Users/wanbaep2/Desktop/FIN513/Homework/HW7")
result = read.csv("problem5.csv")
hist(result$VALUE, xlab = "Value", main = "Histogram")
summary(result$VALUE)
setwd("/Users/park-wanbae/Desktop/MFE/2018-1/FIN513/Homework/HW8")
cva = read.csv("problem3.csv")

plot(cva$Correlation, cva$Value, type = 'l',
    xlab = "Correlation", ylab = "CVA")

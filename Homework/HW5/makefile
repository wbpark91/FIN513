#Makefile

#UGL Coding
#BASE = /Users/wanbaep2/Desktop
#LOC = $(BASE)/FIN514/Code
EFILE = $(BASE)/FIN513/Homework/HW5/Result

#Home Coding
BASE = /Users/park-wanbae/Desktop
LOC = $(BASE)/MFE/2018-1/FIN514/Code
OBJS = derivatives.o *option.o *payoff.o normal.o u_math.o
INCLS = -I$(LOC)
CFLAGS = -std=c++11 -o
#EFILE = $(BASE)/MFE/2018-1/FIN513/Homework/HW6/Result

all: problem3 problem4a problem4b
derivative:
	g++ $(INCLS) -c $(LOC)/derivatives.cpp

option:
	g++ $(INCLS) -c $(LOC)/plainvanilla_option.cpp \
					$(LOC)/european_option.cpp \
					$(LOC)/straddle.cpp	\
					$(LOC)/option.cpp

payoff:
	g++ $(INCLS) -c	$(LOC)/plainvanilla_payoff.cpp

etc:
	g++ $(INCLS) -c $(LOC)/normal.cpp $(LOC)/u_math.cpp

problem3: derivative option payoff etc
	g++ $(INCLS) $(CFLAGS) problem3_b main.cpp $(OBJS) straddle.o

problem4a: etc
	g++ $(INCLS) $(CFLAGS) problem4_a main2.cpp normal.o u_math.o

problem4b: etc
	g++ $(INCLS) $(CFLAGS) problem4_b main3.cpp normal.o u_math.o

clear:
	rm -f derivatives.o
	rm -f *option.o
	rm -f *payoff.o
	rm -f normal.o
	rm -f straddle.o
	rm -f u_math.o

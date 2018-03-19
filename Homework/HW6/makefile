#Makefile

#UGL Coding
#BASE = /Users/wanbaep2/Desktop
#LOC = $(BASE)/Derivatives
EFILE = $(BASE)/FIN513/Homework/HW6/Result

#Home Coding
BASE = /Users/park-wanbae/Desktop
LOC = $(BASE)/MFE/2018-1/Derivatives
ETC = $(LOC)/etc
OPTION = $(LOC)/option
OBJS = derivatives.o *option.o *payoff.o normal.o u_math.o
INCLS = -I$(ETC) -I$(OPTION)
CFLAGS = -std=c++11 -o
#EFILE = $(BASE)/MFE/2018-1/FIN513/Homework/HW6/Result

all: problem2
derivative:
	g++ $(INCLS) -c $(OPTION)/derivatives.cpp

option:
	g++ $(INCLS) -c $(OPTION)/plainvanilla_option.cpp \
					$(OPTION)/european_option.cpp \
					$(OPTION)/option.cpp

payoff:
	g++ $(INCLS) -c	$(OPTION)/plainvanilla_payoff.cpp

etc:
	g++ $(INCLS) -c $(ETC)/normal.cpp $(ETC)/u_math.cpp

problem2: derivative option payoff etc
	g++ $(INCLS) $(CFLAGS) FIN513_HW6 FIN513_HW6.cpp $(OBJS)

clear:
	rm -f derivatives.o
	rm -f *option.o
	rm -f *payoff.o
	rm -f normal.o
	rm -f u_math.o
